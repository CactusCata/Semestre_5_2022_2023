#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "list.h"

// Peut etre a revoir cette structure
typedef struct {
  unsigned int edgeAmount;
  List *listAdj;
} GraphList;


#endif
