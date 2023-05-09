#include "matrix.h"

void matrix_free(Matrix m) {
  free(m);
}

Matrix matrix_create(uint l, uint c) {
  Matrix m = (Vec*) calloc(sizeof(Vec), l);
  return m;
}

void matrix_print(Matrix mat, uint l, uint c, enum MAJOR_TYPE major_type) {
  if (major_type == LINE_MAJOR) {
    printf("Lecture en LINE_MAJOR\n");
    for (uint i = 0; i < l; i++) {
      vec_print(mat[i], c);
      printf("\n");
    }
  } else if (major_type == COL_MAJOR) {
    printf("Lecture en COL_MAJOR\n");
    for (uint line = 0; line < c; line++) {
      printf("(");
      for (uint col = 0; col < l - 1; col++) {
        printf("%d,", (mat[col] >> line) & 1);
      }
      printf("%d", (mat[l - 1] >> line) & 1);
      printf(")\n");
    }
  } else {
    printf("Unknow major type.\n");
  }
}

Matrix get_matrix_generatrice() {
  // représentation en col majeur
  Matrix m = matrix_create(7, 4);

  m[0] = 1;
  m[1] = 2;
  m[2] = 4;
  m[3] = 8;
  m[4] = 7;
  m[5] = 14;
  m[6] = 11;

  return m;
}

Vec encode(Matrix g, Vec v, uint k, uint n) {
  Vec res = 0;
  for (int c = k - 1; c >= 0; c--) {
    res <<= 1;
    res |= vec_hamming_weight(g[c] & v, k) & 1;
  }
  return res;
}

// G = col majeur
// H = ligne majeur
