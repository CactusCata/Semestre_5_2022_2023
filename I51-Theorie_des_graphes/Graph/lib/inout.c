#include "inout.h"

Graph readGraph(char *fileName) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("File %s doesn't exist.\n", fileName);
    exit(0);
  }

  Graph graph;
  unsigned int edgeAmount = -1;
  int x, y;

  char LINE_BUFFER[1024];
  while (fgets(LINE_BUFFER, 1024, file)) {
    if (LINE_BUFFER[0] == 'e') {
      sscanf(LINE_BUFFER, "edgeAmount=%d", &edgeAmount);
      graph = initGraph(edgeAmount);
    } else {
      if (edgeAmount == -1) {
        printf("Le nombre de sommet n'a pas été définie.\n");
        exit(0);
      }
      if (sscanf(LINE_BUFFER, "%d %d", &x, &y)) {
        graph.matrixAdj[x][y] = graph.matrixAdj[y][x] = 1;
      }
    }
  }

  fclose(file);
  return graph;

}

void writeGraph(Graph graph, char *fileName) {

  FILE *file = fopen(fileName, "w");

  fprintf(file, "edgeAmount=%d\n", graph.edgeAmount);

  for (unsigned int i = 0; i < graph.edgeAmount; i++) {
    for (unsigned int j = i + 1; j < graph.edgeAmount; j++) {
      if (graph.matrixAdj[i][j]) {
          fprintf(file, "%d %d\n", i, j);
      }
    }
  }

  fclose(file);

}
