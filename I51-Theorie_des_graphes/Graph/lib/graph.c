#include "graph.h"

Graph initGraph(unsigned int edgeAmount) {
  Graph g;
  g.edgeAmount = edgeAmount;

  unsigned char **matrixAdj = (unsigned char **) malloc(sizeof(unsigned char *) * edgeAmount);
  for (unsigned int i = 0; i < edgeAmount; i++) {
    matrixAdj[i] = calloc(edgeAmount, sizeof(unsigned char));
  }
  g.matrixAdj = matrixAdj;
  return g;
}

void printGraph(Graph graph) {
  unsigned int n = graph.edgeAmount;
  printf("edgeAmount=%d\n", n);
  printf("[\n");
  for (unsigned int i = 0; i < n; i++) {
    printf("\t[");
    for (unsigned int j = 0; j < n - 1; j++) {
      printf("%d, ", graph.matrixAdj[i][j]);
    }
    printf("%d]\n", graph.matrixAdj[i][n - 1]);
  }
  printf("]\n");
}

void drawGraph(Graph graph, char *path, char *fileName) {
  unsigned int n = graph.edgeAmount;

  char filePathNameExtension[256];
  sprintf(filePathNameExtension, "%s%s.dot", path, fileName);
  FILE *file = fopen(filePathNameExtension, "w");

  fprintf(file, "graph A {\n");

  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = i + 1; j < n; j++) {
      if (graph.matrixAdj[i][j] == 1) {
        fprintf(file, "\t%d -- %d\n", i, j);
      }
    }
  }

  fprintf(file, "}");
  fclose(file);
  
  char cmd[256];
  sprintf("dot -Tpng %s > %s.png", filePathNameExtension, fileName);
  printf("%s\n", cmd);
  system(cmd);

}
