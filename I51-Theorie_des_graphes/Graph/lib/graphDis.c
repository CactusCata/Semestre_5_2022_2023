#include "graphDis.h"

GraphD *singleton(int s) {
  GraphD *g = (GraphD *) malloc(sizeof(GraphD));
  g->s = s;
  g->size = 1;
  g->representant = g;
  g->next = NULL;
  g->last = g;
  return g;
}

/**
*   Renvoie le représentant d'un des ensembles disjoints
*/
GraphD *representant(GraphD **tab, int s) {
  return tab[s]->representant;
}

void reunion(GraphD *g1, GraphD *g2) {
  GraphD *tmp;
  if (g1->size > g2->size) {
    tmp = g1;
    g1 = g2;
    g2 = tmp;
  }

  g2->size += g1->size;
  tmp = g1;
  while (tmp != NULL) {
    tmp->representant = g2;
    tmp = tmp->next;
  }

  g2->last->next = g1;
  g2->last = g1->last;
}
