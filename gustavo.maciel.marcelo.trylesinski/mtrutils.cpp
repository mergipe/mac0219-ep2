#include "mtrutils.h"

#include <cinttypes>
#include <cstdlib>

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
    matrix *matrices;
    char temp[3];

    fscanf(file, "%d", matrices_num);
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

    return matrices;
}

