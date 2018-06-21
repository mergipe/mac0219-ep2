#include "mtrutils.h"
#include "reduce.cuh"

#include <cstdio>
#include <cstdlib>

// Número de argumentos na linha de comando.
static const int arg_num = 1;

// Dimensões das matrizes.
static const int matrices_dim = 3;

int main(int argc, char **argv)
{
    FILE *matrices_file;
    matrix *matrices, result_seq, result_cuda;
    int matrices_num;

    if (argc != arg_num + 1)
    {
        fprintf(stderr, "Usage: test MATRICES_FILE_PATH\n");
        return EXIT_FAILURE;
    }

    matrices_file = fopen(argv[1], "r");

    if (matrices_file == NULL)
    {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    matrices = read_matrices(&matrices_num, matrices_dim, matrices_file);
    fclose(matrices_file);
    result_seq = mtralloc(matrices_dim);
    result_cuda = mtralloc(matrices_dim);
    sequential_reduce(matrices, result_seq, matrices_dim);
    cuda_reduce(matrices, result_cuda, matrices_dim);
    printf("SEQUENTIAL REDUCE:\n");
    print_matrix(result_seq, matrices_dim);
    printf("\n");
    printf("CUDA REDUCE:\n");
    print_matrix(result_cuda, matrices_dim);

    for (int i = 0; i < matrices_num; i++)
        mtrfree(matrices[i]);
    free(matrices);
    mtrfree(result_seq);
    mtrfree(result_cuda);

    return EXIT_SUCCESS;
}
