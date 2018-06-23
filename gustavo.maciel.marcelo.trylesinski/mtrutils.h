#ifndef MTRUTILS_H_
#define MTRUTILS_H_

#include <cstdio>
#include <cstdint>

// Tipos matrix e vector.
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

// Devolve uma matriz nxn aleatória, com elementos entre 1 e 100.
void mtrrand(matrix mtr, int n);

// Recebe duas matrizes nxn, A e B. Devolve true se A = B, e false caso
// contrário.
bool mtreq(matrix A, matrix B, int n);

#endif
