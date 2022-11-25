#ifndef GRAPH_DIS_H
#define GRAPH_DIS_H

#include <stdlib.h>

typedef struct graphD {
  int s;
  int size;
  struct graphD *next;
  struct graphD *representant;
  struct graphD *last;
} graphD;

graphD *initGraphD(int n);

graphD *singleton(int s);

graphD *representant(graphD **tab, int s);

void reunion(graphD *g1, graphD *g2);

#endif
