#ifndef MATRIX_H

#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

typedef Vec* Matrix;

typedef int* Syndrome;

// Supprime la matrice de la mémoire
void matrix_free(Matrix matrix, uint l);

// Crée une matrice de l lignes et de c colonnes
Matrix matrix_create(uint l, uint c);

// Affiche une matrice de l lignes et de c colonnes
void matrix_print(Matrix mat, uint l, uint c);

// Renvoie la transposé de la matrice
Matrix matrix_transpose(Matrix matrix, uint k, uint n);

// Renvoie la matrice génératrice G
Matrix get_generatice_matrix();

// Renvoie la matrice de controle H
Matrix get_control_matrix();

// Encode le vecteur v grâce à la matrice génératrice g
Vec encode(Matrix g, Vec v, uint k, uint n);

Syndrome syndrome(Matrix h, Vec c, uint k, uint n);

#endif
