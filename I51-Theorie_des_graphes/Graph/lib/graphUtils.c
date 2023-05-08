#include "graphUtils.h"

int compareArete(const void *a1, const void *a2) {
  float sizeA1 = ((arete *) a1)->w;
  float sizeA2 = ((arete *) a2)->w;

  if (sizeA1 > sizeA2) return +1;
  if (sizeA1 < sizeA2) return -1;
  return 0;
}

void drawPoints(char *path, char *fileName, point *points, int pointAmount) {
  char tmp[512];

  sprintf(tmp, "%s/%s.dot", path, fileName);
  FILE *file = fopen(tmp, "w");

  if (file == NULL) {
    perror("drawPoints(...)");
    exit(0);
  }

  fputs("graph G {\n", file);
  for (int i = 0; i < pointAmount; i++) {
    fprintf(file, "\tnode_%d [pos=\"%f,%f!\",shape=circle];\n", i, points[i].x, points[i].y);

  }

  fputs("}", file);
  fclose(file);
}

void dotToImage(char *path, char *fileName) {
  char cmd[512];
  sprintf(cmd, "dot -Kfdp -n -Tpng -o %s%s.png %s%s.dot", path, fileName, path, fileName);
  system(cmd);
}

void openImage(char *path, char *fileName, char *extension) {
  char cmd[512];
  sprintf(cmd, "feh %s%s.%s", path, fileName, extension);
  system(cmd);
}
