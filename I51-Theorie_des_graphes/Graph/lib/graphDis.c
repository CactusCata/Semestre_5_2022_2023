#include "graphDis.h"

graphD *singleton(int s) {
  graphD *g = (graphD *) malloc(sizeof(graphD));
  g->s = s;
  g->size = 1;
  g->representant = g;
  g->next = NULL;
  g->last = g;
  return g;
}

// A mettre à jour
graphD *representant(graphD **tab, int s) {
  graphD *aux = tab[s];
  while (aux->next != aux) {
    aux = aux->next;
  }
  return aux;
}

void reunion(graphD *g1, graphD *g2) {
  graphD *tmp;
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

graphD *initGraphD(int n) {
  graphD *g = (graphD *) malloc(sizeof(graphD) * n);

  

  return g;
}
