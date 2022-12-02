#ifndef GRAPH_ACM_H
#define GRAPH_ACM_H

#include "graphMatAdj.h"
#include "graphUtils.h"

typedef struct {
  GraphM graph;

  point *points;
  int pointAmount;
} GraphAcm;

void drawGraphAcm(GraphAcm graph, char *path, char *fileName);
// Créer un fichier .png à partir du graph correspondant

void freeGraphAcm(GraphAcm graph);

#endif
