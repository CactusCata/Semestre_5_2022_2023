#ifndef ACM_H
#define ACM_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "graphUtils.h"
#include "graphMatAdj.h"
#include "graphAcm.h"
#include "graphDis.h"
#include "mathUtils.h"

point *nuages(int n);

// utilise l'algo de krushka
GraphAcm acm(point *points, int n);

void approximation(GraphM g, int depart);

void parcours(GraphM *g, int s, int p, int *libre, int *k);

#endif
