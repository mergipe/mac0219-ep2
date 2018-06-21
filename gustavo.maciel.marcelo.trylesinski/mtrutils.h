#ifndef MTRUTILS_H_
#define MTRUTILS_H_

#include <cstdio>
#include <cstdint>

// Tipo matrix.
typedef int32_t *matrix;

// Aloca e devolve uma matriz nxn vazia.
matrix mtralloc(int n);

// Libera o espaço ocupado pela matriz mtr.
void mtrfree(matrix mtr);

// Mostra a matriz mtr nxn em stdout.
void print_matrix(matrix mtr, int n);

// Lê o arquivo de matrizes apontado por file, armazena o número de matrizes
// do arquivo em matrices_num e devolve um vetor com as matrizes lidas.
matrix *read_matrices(int *matrices_num, int matrices_dim, FILE *file);

#endif
