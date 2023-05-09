#ifndef VECTOR_H

#include "../utils.h"

typedef unsigned char Vec;

Vec vec_create(uint n);

void vec_print(Vec v, uint n);

Vec* mots(uint k);

uint vec_hamming_weight(Vec v, uint n);

Vec vec_diff(Vec u, Vec v, int n);

uint vec_hamming_distance(Vec u, Vec v, int n);

uint dist_min(Vec* vecteurs, uint n, uint nb_vect);

#endif
