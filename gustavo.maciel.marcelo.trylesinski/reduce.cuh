#ifndef REDUCE_H_
#define REDUCE_H_

#include "mtrutils.h"

// Reduz matrices (conjunto com matrices_num matrizes com dimensões
// matrices_dim) sequencialmente, com respeito à operação definida no
// enunciado, e armazena o resultado em result.
void sequential_reduce(matrix *matrices, int matrices_num, matrix result,
                       int matrices_dim);

// Reduz matrices (conjunto com matrices_num matrizes com dimensões
// matrices_dim), utilizando CUDA, com respeito à operação definida no
// enunciado, e armazena o resultado em result.
void cuda_reduce(matrix *matrices, int matrices_num, matrix result,
                 int matrices_dim);

#endif
