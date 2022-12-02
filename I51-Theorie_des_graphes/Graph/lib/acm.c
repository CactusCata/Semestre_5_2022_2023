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

GraphAcm acm(point *points, int n) {
    GraphM g = initGraphM(n);
    int areteAmount = (n * (n - 1)) >> 1;
    arete *aretes = (arete *) calloc(areteAmount, sizeof(arete));

    int k = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        aretes[k].i = i;
        aretes[k].j = j;
        aretes[k].w = distance(points[i], points[j]);
        printf("distance(%d, %d) = %f\n", i, j, aretes[k].w);
        k++;
      }
    }

    qsort(aretes, areteAmount, sizeof(arete), compareArete);

    // Initialisation de la structure d'ensemble disjoint
    GraphD **dis = (GraphD **) calloc(g.edgeAmount, sizeof(GraphD *));
    for (int i = 0; i < g.edgeAmount; i++) {
      dis[i] = singleton(i);
    }

    for (int i = 0; i < areteAmount; i++) {
      arete currentArete = aretes[i];
      int x = currentArete.i;
      int y = currentArete.j;
      if (representant(dis, x) != representant(dis, y)) {
        reunion(representant(dis, x), representant(dis, y));
        g.matrixAdj[x][y] = 1;
        g.matrixAdj[y][x] = 1;
      }
    }

    free(aretes);

    GraphAcm graphAcm;
    graphAcm.graph = g;
    graphAcm.points = points;
    graphAcm.pointAmount = n;
    return graphAcm;

}

void approximation(GraphM g, int depart) {
  int libre[g.edgeAmount];
  for (int i = 0; i < g.edgeAmount; i++) {
    libre[i] = 1;
  }
  g.chemin = calloc(g.edgeAmount, sizeof(int));
  int k = 0;
  parcours(&g, depart, 0, libre, &k);
}

// Segmentation fault ici, corriger la prochaine fois
void parcours(GraphM *g, int s, int p, int *libre, int *k) {
  g->chemin[(*k)++] = s;
  for (int t = 0; t < g->edgeAmount; t++) {
    if (libre[t] && g->matrixAdj[s][t]) {
      libre[t] = 1;
      parcours(g, t, p+1, libre, k);
    }
  }
}
