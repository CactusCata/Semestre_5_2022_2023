#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned int representant;
    unsigned int composanteSize;
} InfoGraph;

/** ==================================
*   =    Poins, Nuages de points     =
*   ==================================
*/

typedef struct point {
  float x, y;
} point;

void drawPoints(char *path, char *fileName, point *points, int pointAmount);

void dotToImage(char *path, char *fileName);

void openImage(char *path, char *fileName, char *extension);

/** ==================================
*   =            Aretes              =
*   ==================================
*/

typedef struct arete {
  int i, j;
  float w; // distance de i à j
} arete;

int compareArete(const void *a1, const void *a2);

#endif
