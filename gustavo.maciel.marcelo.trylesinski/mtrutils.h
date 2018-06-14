#ifndef MTRUTIL_H
#define MTRUTIL_H

#include <cstdint>

typedef int32_t *matrix;

matrix mtralloc(int n);
void mtrfree(matrix mtr);

#endif
