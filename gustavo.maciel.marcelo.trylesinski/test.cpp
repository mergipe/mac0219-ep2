#include "mtrutils.h"
#include "reduce.cuh"

#include <cstdio>
#include <cstdlib>

// Dimensões das matrizes.
static const int matrices_dim = 3;

// Número de matrizes.
static const int matrices_num = 3;

int main(int argc, char **argv)
{
    matrix *matrices, result_seq, result_cuda;

    matrices = (matrix *) malloc(matrices_num * sizeof (matrix));

    for (int i = 0; i < matrices_num; i++)
    {
        matrices[i] = mtralloc(matrices_dim);
        mtrrand(matrices[i], matrices_dim);
    }

    result_seq = mtralloc(matrices_dim);
    result_cuda = mtralloc(matrices_dim);
    sequential_reduce(matrices, matrices_num, result_seq, matrices_dim);
    cuda_reduce(matrices, matrices_num, result_cuda, matrices_dim);
    printf("SEQUENTIAL REDUCE:\n");
    print_matrix(result_seq, matrices_dim);
    printf("\n");
    printf("CUDA REDUCE:\n");
    print_matrix(result_cuda, matrices_dim);

    if (mtreq(result_seq, result_cuda, matrices_dim))
        printf("\nOK\n");
    else
        printf("\nFAIL\n");

    for (int i = 0; i < matrices_num; i++)
        mtrfree(matrices[i]);

    free(matrices);
    mtrfree(result_seq);
    mtrfree(result_cuda);

    return EXIT_SUCCESS;
}
