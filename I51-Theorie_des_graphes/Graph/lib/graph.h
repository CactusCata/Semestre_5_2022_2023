#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int edgeAmount;
  unsigned char **matrixAdj;
} Graph;

Graph initGraph(unsigned int edgeAmount);

void printGraph(Graph graph);

void drawGraph(Graph graph, char *path, char *fileName);

#endif
