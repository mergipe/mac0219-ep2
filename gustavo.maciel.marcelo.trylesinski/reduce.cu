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

// 
__global__ void cuda_reduce_kernel(matrix *matrices, int matrices_num,
                                   matrix result, int matrices_dim)
{
}

void sequential_reduce(matrix *matrices, int matrices_num, matrix result,
                       int matrices_dim)
{
    binary_reduce(matrices[0], matrices[1], result, matrices_dim);

    for (int i = 2; i < matrices_num; i++)
        binary_reduce(result, matrices[i], result, matrices_dim);
}

void cuda_reduce(matrix *matrices, int matrices_num, matrix result,
                 int matrices_dim)
{
}
