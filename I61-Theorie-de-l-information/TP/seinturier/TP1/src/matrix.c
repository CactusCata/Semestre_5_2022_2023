#include "matrix.h"

void matrix_free(Matrix matrix, uint l) {
    for (uint i = 0; i < l; i++) {
        vec_free(matrix[i]);
    }
    free(matrix);
}

Matrix matrix_create(uint line, uint col) {
    Matrix m = malloc(sizeof(Vec *) * line);
    for (uint l = 0; l < line; l++) {
        m[l] = vec_create(col);
    }
    return m;
}

Matrix get_generatice_matrix() {
    uint line = 4;
    uint col = 7;
    Matrix m = matrix_create(line, col);

    m[0][0] = 1;
    m[0][4] = 1;
    m[0][6] = 1;

    m[1][1] = 1;
    m[1][4] = 1;
    m[1][5] = 1;
    m[1][6] = 1;

    m[2][2] = 1;
    m[2][4] = 1;
    m[2][5] = 1;

    m[3][3] = 1;
    m[3][5] = 1;
    m[3][6] = 1;

    return m;
}

Matrix get_control_matrix() {
    uint line = 3;
    uint col = 7;

    Matrix m = matrix_create(line, col);

    m[0][0] = 1;
    m[0][1] = 1;
    m[0][2] = 1;
    m[0][4] = 1;

    m[1][1] = 1;
    m[1][2] = 1;
    m[1][3] = 1;
    m[1][5] = 1;

    m[2][0] = 1;
    m[2][1] = 1;
    m[2][3] = 1;
    m[2][6] = 1;

    return m;
}

void matrix_print(Matrix mat, uint l, uint c) {
    for (uint i = 0; i < l; i++) {
        printf("[");
        for (uint j = 0; j < c - 1; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("%d", mat[i][c - 1]);
        printf("]\n");
    }
}

Vec encode(Matrix g, Vec v, uint k, uint n) {
    Vec c = vec_create(n);

    for (uint line = 0; line < k; line++) {
        for (uint col = 0; col < n; col++) {
            c[col] ^= (v[line] & g[line][col]);
        }
    }
    return c;
}

Matrix matrix_transpose(Matrix matrix, uint k, uint n) {
    Matrix matrix_t = matrix_create(n, k);
    for (uint l = 0; l < k; l++) {
        for (uint c = 0; c < n; c++) {
            matrix_t[c][l] = matrix[l][c];
        }
    }
    return matrix_t;
}


Syndrome syndrome(Matrix h, Vec c, uint k, uint n) {
    Syndrome syndrome = vec_create(n - k);
    for (uint i = 0; i < (n - k); i++) {
        for (uint j = 0; j < n; j++) {
            syndrome[i] ^= c[j] & h[j][i];
        }
    }
    return syndrome;
}
