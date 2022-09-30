#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef struct {
  unsigned int edgeAmount;
  unsigned char **matrixAdj;
} Graph;

void printGraph(Graph graph);

#endif
