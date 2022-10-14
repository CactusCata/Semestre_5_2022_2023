#include "graphList.h"

Graph initGraph(unsigned int edgeAmount) {
  GraphList graph;
  graph.edgeAmount = edgeAmount;

  // A CONTINUER



  g.edgeAmount = edgeAmount;

  unsigned char **matrixAdj = (unsigned char **) malloc(sizeof(unsigned char *) * edgeAmount);
  for (unsigned int i = 0; i < edgeAmount; i++) {
    matrixAdj[i] = calloc(edgeAmount, sizeof(unsigned char));
  }
  g.matrixAdj = matrixAdj;
  return g;
}
