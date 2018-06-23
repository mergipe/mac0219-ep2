#include "reduce.cuh"
#include "mtrutils.h"

#include <cmath>

#define R(i,j) R[(i) * matrices_dim + (j)]
#define A(i,j) A[(i) * matrices_dim + (j)]
#define B(i,j) B[(i) * matrices_dim + (j)]

// 
static void binary_reduce(matrix A, matrix B, matrix R, int matrices_dim)
{
    for (int i = 0; i < matrices_dim; i++)
        for (int j = 0; j < matrices_dim; j++)
            R(i,j) = fmin(A(i,j), B(i,j));
}

void sequential_reduce(matrix *matrices, int matrices_num, matrix result,
                       int matrices_dim)
{
    binary_reduce(matrices[0], matrices[1], result, matrices_dim);

    for (int i = 2; i < matrices_num; i++)
        binary_reduce(result, matrices[i], result, matrices_dim);
}

//
__inline__ __device__ int32_t warp_reduce_min(int32_t val)
{
    printf("%d ", val);

    for (int offset = warpSize / 2; offset > 0; offset /= 2)
        val = min(val, __shfl_down_sync(val, offset, warpSize));

    return val;
}

//
__inline__ __device__ int32_t block_reduce_min(int32_t val)
{
    static __shared__ int32_t shared[32];
    int laneid, warpid;

    laneid = threadIdx.x % warpSize;
    warpid = threadIdx.x / warpSize;

    val = warp_reduce_min(val);
    if (laneid == 0) shared[warpid] = val;
    __syncthreads();

    val = (threadIdx.x < blockDim.x / warpSize) ? shared[laneid] : INT32_MAX;
    if (warpid == 0) val = warp_reduce_min(val);

    return val;
}

// 
__global__ void cuda_reduce_kernel(int32_t *in, int32_t *out, int n)
{
    int minimum = INT32_MAX;

    for (int i = blockIdx.x * blockDim.x + threadIdx.x;
         i < n;
         i += blockDim.x * gridDim.x)
    {
        minimum = in[i];
    }

    minimum = block_reduce_min(minimum);

    if (threadIdx.x == 0)
        out[blockIdx.x] = minimum;
}

void cuda_reduce(matrix *matrices, int matrices_num, matrix result,
                 int matrices_dim)
{
    int32_t **temp_matrices;
    int32_t *dev_vector, *dev_result, *h_result;
    size_t in_size, out_size;
    int vector_rows, vector_cols, threads_per_block, blocks_per_grid;

    vector_rows = matrices_dim * matrices_dim;
    vector_cols = matrices_num;
    temp_matrices = (int32_t **) malloc(vector_rows * sizeof (int32_t *));

    while (vector_cols % 32 != 0)
        vector_cols++;

    threads_per_block = min(vector_cols, 1024);
    in_size = max(threads_per_block, vector_cols) * sizeof (int32_t);

    for (int i = 0; i < vector_rows; i++)
    {
        blocks_per_grid = (vector_cols / threads_per_block) + 1;
        out_size = blocks_per_grid * sizeof (int32_t);
        temp_matrices[i] = (int32_t *) malloc(in_size);

        for (int j = 0; j < matrices_num; j++)
            temp_matrices[i][j] = matrices[j][i];

        for (int j = matrices_num; j < vector_cols; j++)
            temp_matrices[i][j] = INT32_MAX;

        h_result = (int32_t *) malloc(out_size);
        cudaMalloc(&dev_vector, in_size);
        cudaMalloc(&dev_result, out_size);
        cudaMemcpy(dev_vector, temp_matrices[i], in_size,
                   cudaMemcpyHostToDevice);
        cuda_reduce_kernel<<<blocks_per_grid, threads_per_block>>>
            (dev_vector, dev_result, vector_cols);
        cuda_reduce_kernel<<<1, blocks_per_grid>>>
            (dev_result, dev_result, blocks_per_grid);
        cudaMemcpy(h_result, dev_result, out_size, cudaMemcpyDeviceToHost);
printf("%d \n", h_result[0]);
        cudaFree(dev_vector);
        cudaFree(dev_result);
    }

    for (int i = 0; i < vector_rows; i++)
        free(temp_matrices[i]);

    free(temp_matrices);
}
