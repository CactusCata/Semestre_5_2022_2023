#include "graphMatAdj.h"

GraphM initGraphM(unsigned int edgeAmount) {
  GraphM g;
  g.edgeAmount = edgeAmount;

  unsigned char **matrixAdj = (unsigned char **) malloc(sizeof(unsigned char *) * edgeAmount);
  for (unsigned int i = 0; i < edgeAmount; i++) {
    matrixAdj[i] = calloc(edgeAmount, sizeof(unsigned char));
  }
  g.matrixAdj = matrixAdj;
  return g;
}

GraphM initGraphMFromFile(char *fileName) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("File %s doesn't exist.\n", fileName);
    exit(0);
  }

  GraphM graph;
  unsigned int edgeAmount = -1;
  int x, y;

  char LINE_BUFFER[1024];
  while (fgets(LINE_BUFFER, 1024, file)) {
    if (LINE_BUFFER[0] == 'e') {
      sscanf(LINE_BUFFER, "edgeAmount=%d", &edgeAmount);
      graph = initGraphM(edgeAmount);
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

void writeGraphMInFile(GraphM graph, char *fileName) {
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

void freeGraphM(GraphM graph) {
  for (size_t i = 0; i < graph.edgeAmount; i++) {
    free(graph.matrixAdj[i]);
  }
  free(graph.matrixAdj);
}

void printGraphM(GraphM graph) {
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

void drawGraphM(GraphM graph, char *path, char *fileName) {
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

size_t getComposanteConnexeAmountM(GraphM graph) {
  unsigned char *reached = (unsigned char *) calloc(sizeof(unsigned char), graph.edgeAmount);
  size_t composanteConnexeAmount = 0;
  for (size_t s = 0; s < graph.edgeAmount; s++) {
    if (!reached[s]) {
      composanteConnexeAmount++;
      reachAllNeighborsM(s, graph, reached);
    }
  }
  free(reached);
  return composanteConnexeAmount;
}

void reachAllNeighborsM(size_t s, GraphM graph, unsigned char *reached) {
  if (!reached[s]) {
    reached[s] = 1;
    for (size_t sNeighbors = 0; sNeighbors < graph.edgeAmount; sNeighbors++) {
      if (graph.matrixAdj[s][sNeighbors]) {
        reachAllNeighborsM(sNeighbors, graph, reached);
      }
    }
  }
}
