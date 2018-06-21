#include "reduce.cuh"
#include "mtrutils.h"

//
__global__ void cuda_reduce_kernel(matrix *matrices, matrix result,
                                   int matrices_dim)
{
}

void sequential_reduce(matrix *matrices, matrix result, int matrices_dim)
{
}

void cuda_reduce(matrix *matrices, matrix result, int matrices_dim)
{
}
