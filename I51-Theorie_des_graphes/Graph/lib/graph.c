#include "graph.h"

void printGraph(Graph graph) {
  printf("edgeAmount=%d\n", graph.edgeAmount);
  printf("[\n");
  for (unsigned int i = 0; i < graph.edgeAmount; i++) {
    printf("\t[");
    for (unsigned int j = 0; j < graph.edgeAmount; j++) {
      printf("%d ", graph.matrixAdj[i][j]);
    }
    printf("]");
  }
  printf("]\n");
}
