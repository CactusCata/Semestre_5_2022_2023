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

void freeGraph(Graph graph) {
  for (size_t i = 0; i < graph.edgeAmount; i++) {
    free(graph.matrixAdj[i]);
  }
  free(graph.matrixAdj);
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

  if (!file) {
    printf("The file '%s' do not exist.\n", filePathNameExtension);
    exit(1);
  }

  fprintf(file, "graph A {\n");

  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = i + 1; j < n; j++) {
      if (graph.matrixAdj[i][j] == 1) {
        fprintf(file, "\t%d -- %d;\n", i, j);
      }
    }
  }

  fprintf(file, "}");
  fclose(file);

  char cmd[512];
  sprintf(cmd, "dot -Tpng %s > %s%s.png", filePathNameExtension, path, fileName);
  system(cmd);

}

size_t getComposanteConnexeAmount(Graph graph) {
  unsigned char *reached = (unsigned char *) calloc(sizeof(unsigned char), graph.edgeAmount);
  size_t composanteConnexeAmount = 0;
  for (size_t s = 0; s < graph.edgeAmount; s++) {
    if (!reached[s]) {
      composanteConnexeAmount++;
      reachAllNeighbors(s, graph, reached);
    }
  }
  free(reached);
  return composanteConnexeAmount;
}

void reachAllNeighbors(size_t s, Graph graph, unsigned char *reached) {
  if (!reached[s]) {
    reached[s] = 1;
    for (size_t sNeighbors = 0; sNeighbors < graph.edgeAmount; sNeighbors++) {
      if (graph.matrixAdj[s][sNeighbors]) {
        reachAllNeighbors(sNeighbors, graph, reached);
      }
    }
  }
}
