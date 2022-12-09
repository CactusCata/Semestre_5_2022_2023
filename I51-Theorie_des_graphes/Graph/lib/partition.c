#include "partition.h"

void partition(int p, int s, int *t, int *solution) {
  if (s == 0) {
    (*solution)++;
    return;
  }

  if (s < p) return;

  for (int i = 0; i * p <= s; i++) {
    t[p] = i;
    partition(p + 1, s - i * p, t, solution);
  }
  t[p] = 0;
}
