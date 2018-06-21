#include "mtrutils.h"

#include <cinttypes>
#include <cstdlib>
#include <ctime>

matrix mtralloc(int n)
{
    matrix mtr;

    mtr = (matrix) malloc(n * n * sizeof (int32_t));

    return mtr;
}

void mtrfree(matrix mtr)
{
    free(mtr);
}

void print_matrix(matrix mtr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", mtr[i * n + j]);

        printf("\n");
    }
}

matrix *read_matrices(int *matrices_num, int matrices_dim, FILE *file)
{
    int *matrices_num_t;
    matrix *matrices;
    char temp[3];

    matrices_num_t = (int *) malloc(sizeof (int));
    fscanf(file, "%d", matrices_num_t);
    *matrices_num = *matrices_num_t;
    matrices = (matrix *) malloc(*matrices_num * sizeof (matrix));

    for (int n = 0; n < *matrices_num; n++)
    {
        matrices[n] = mtralloc(matrices_dim);

        if (matrices[n] == NULL)
        {
            perror("Erro: ");
            exit(EXIT_FAILURE);
        }

        fscanf(file, "%s", temp);

        for (int i = 0; i < matrices_dim; i++)
            for (int j = 0; j < matrices_dim; j++)
                fscanf(file, "%" SCNd32, &matrices[n][i * matrices_dim + j]);
    }

    free(matrices_num_t);

    return matrices;
}

void mtrrand(matrix mtr, int n)
{
    srand(time(NULL));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mtr[i * n + j] = rand() % 100 + 1;
}

bool mtreq(matrix A, matrix B, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i * n + j] != B[i * n + j])
                return false;
        }
    }

    return true;
}
