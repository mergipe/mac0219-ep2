#include "mtrutils.h"

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
