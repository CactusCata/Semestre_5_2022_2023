#include "vector.h"


Vec vecteur_vide(uint n) {
  return 0;
}

void vec_print(Vec v, uint n) {
  printf("(");
  if (n != 0) {
    for (uint i = 0; i < n - 1; i++) {
      printf("%d,", v & 1);
      v >>= 1;
    }
    printf("%d", v & 1);
  }

  printf(")");
}

Vec* vec_get_all_possibilities(uint k) {
  Vec *all = calloc(sizeof(Vec), 1 << k);
  for (uint i = 0; i < 1 << k; i++) {
    all[i] = i;
  }
  return all;
}

uint vec_hamming_weight(Vec v, uint n) {
    uint hamming_weight = 0;
    while (v) {
      v &= v - 1;
      hamming_weight++;
    }
    return hamming_weight;
}

Vec vec_diff(Vec u, Vec v, int n) {
  if (u == 0 || v == 0) {
    return 0;
  }
  return u ^ v;
}

uint vec_hamming_distance(Vec u, Vec v, int n) {
  if (u == 0 || v == 0) {
    return 0;
  }
  return vec_hamming_weight(vec_diff(u, v, n), n);
}

uint dist_min(Vec* vecteurs, uint n, uint nb_vect) {
  uint min_distance = vec_hamming_distance(vecteurs[0], vecteurs[1], n);
  for (uint start = 0; start < nb_vect + 1; start++) {
      for (uint i = start + 1; i < nb_vect; i++) {
          uint distance_hamming = vec_hamming_distance(vecteurs[start], vecteurs[i], n);
          if (distance_hamming < min_distance) {
              min_distance = distance_hamming;
          }
      }
  }
  return min_distance;
}
