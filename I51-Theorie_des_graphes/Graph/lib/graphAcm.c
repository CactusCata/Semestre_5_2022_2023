#include "graphAcm.h"

void drawGraphAcm(GraphAcm graphAcm, char *path, char *fileName) {
  unsigned int n = graphAcm.graph.edgeAmount;

  char filePathNameExtension[256];
  sprintf(filePathNameExtension, "%s%s.dot", path, fileName);
  FILE *file = fopen(filePathNameExtension, "w");

  fprintf(file, "graph A {\n");

  for (int i = 0; i < graphAcm.pointAmount; i++) {
    fprintf(file, "\t%d [pos=\"%f,%f!\",shape=circle];\n", i, graphAcm.points[i].x, graphAcm.points[i].y);
  }

  for (unsigned int i = 0; i < n; i++) {
    for (unsigned int j = i + 1; j < n; j++) {
      if (graphAcm.graph.matrixAdj[i][j] == 1) {
        fprintf(file, "\t%d -- %d;\n", i, j);
      }
    }
  }

  int *chemin = graphAcm.graph.chemin;
  int cursorChemin = 0;
  int last = chemin[cursorChemin++];

  while (cursorChemin < graphAcm.graph.edgeAmount) {
    int next = chemin[cursorChemin++];
    fprintf(file, "\t%d -- %d [color=\"red\"]\n", last, next);
    last = next;
  }

  fprintf(file, "\t%d -- %d [color=\"red\"]\n", chemin[0], last);

  fprintf(file, "}");
  fclose(file);

  char cmd[512];
  sprintf(cmd, "dot -Tpng -Kfdp -n %s -o %s%s.png", filePathNameExtension, path, fileName);
  system(cmd);

}

void freeGraphAcm(GraphAcm graph) {
  freeGraphM(graph.graph);
  free(graph.points);
}
