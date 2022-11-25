#include "acm.h"

point *nuages(int n) {
  srand(getpid());

  point *points = (point *) malloc(sizeof(point) * n);

  for (int i = 0; i < n; i++) {
    points[i].x = (random() - (RAND_MAX >> 1));
    points[i].x /= (RAND_MAX >> 1);
    points[i].y = (random() - (RAND_MAX >> 1));
    points[i].y /= (RAND_MAX >> 1);
  }

  return points;
}

GraphM acm(point *points, int n) {
    GraphM g = initGraphM(n);
    int areteAmount = (n * (n - 1)) >> 1;
    arete *aretes = (arete *) calloc(areteAmount, sizeof(arete));

    int k = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        aretes[k].i = i;
        aretes[k].j = j;
        aretes[k].w = distance(points[i], points[j]);
        k++;
      }
    }

    qsort(aretes, areteAmount, sizeof(arete), compareArete);

    // remplir tous les points de l'acm

    free(aretes);
    return g;

}

void approximation(GraphM *g, int depart) {
  int libre[g->edgeAmount];
  for (int i = 0; i < g->edgeAmount; i++) {
    libre[i] = 1;
  }
  g->chemin = calloc(g->edgeAmount, sizeof(int));
  int k = 0;
  parcours(g, depart, 0, libre, &k);
}

void parcours(GraphM *g, int s, int p, int *libre, int *k) {
  g->chemin[(*k)++] = s;
  for (int t = 0; t < g->edgeAmount; t++) {
    if (libre[t] && g->matrixAdj[s][t]) {
      libre[t] = 1;
      parcours(g, t, p+1, libre, k);
    }
  }
}
