#ifndef MATRIX_H

#include "vector.h"

typedef Vec* Matrix;

typedef Vec Syndrome;

enum MAJOR_TYPE {
  LINE_MAJOR,
  COL_MAJOR
};

void matrix_free(Matrix m);

Matrix matrix_create(uint l, uint c);

void matrix_print(Matrix mat, uint l, uint c, uint order);

Matrix get_matrix_generatrice();

Vec encode(Matrix g, Vec v, uint k, uint n);

Syndrome syndrome(Matrix h, Vec c, uint k, uint n);

#endif
