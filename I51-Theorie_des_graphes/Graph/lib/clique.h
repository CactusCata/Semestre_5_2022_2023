#ifndef CLIQUE
#define CLIQUE

#include "graphMatAdj.h"
#include "utils.h"
#include "stdlib.h"

void getMaximumClique(GraphM *g);

int getCliqueSize(int *array, int arraySize);

void getMaximalClique(GraphM *g, int *currentList, int *currentListCursor, int *blackList, int *blackListCursor);

#endif
