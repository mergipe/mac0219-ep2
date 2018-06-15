#ifndef MTRUTILS_H_
#define MTRUTILS_H_

#include <cstdint>

/* Tipo matrix. */
typedef int32_t *matrix;

/* Aloca e devolve uma matriz nxn vazia. */
matrix mtralloc(int n);

/* Libera o espaço ocupado pela matriz mtr. */
void mtrfree(matrix mtr);

#endif
