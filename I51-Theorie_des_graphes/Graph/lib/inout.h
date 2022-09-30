#ifndef INOUT_H
#define INOUT_H

#include <stdlib.h>
#include "graph.h"

Graph readGraph(char *fileName);

void writeGraph(Graph graph, char *fileName);

Graph initGraph(unsigned int edgeAmount);

#endif
