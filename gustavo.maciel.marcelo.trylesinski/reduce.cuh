#ifndef REDUCE_H_
#define REDUCE_H_

#include "mtrutils.h"

//
void sequential_reduce(matrix *matrices, matrix result, int matrices_dim);

//
void cuda_reduce(matrix *matrices, matrix result, int matrices_dim);

#endif
