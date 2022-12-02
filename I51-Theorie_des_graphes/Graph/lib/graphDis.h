#ifndef GRAPH_DIS_H
#define GRAPH_DIS_H

#include <stdlib.h>

typedef struct GraphD {
  int s;
  int size;
  struct GraphD *next;
  struct GraphD *representant;
  struct GraphD *last;
} GraphD;

GraphD *singleton(int s);

GraphD *representant(GraphD **tab, int s);

void reunion(GraphD *g1, GraphD *g2);

#endif
