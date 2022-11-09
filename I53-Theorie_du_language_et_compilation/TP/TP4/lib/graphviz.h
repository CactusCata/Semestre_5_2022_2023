#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <stdio.h>

void graphVizInitGraph(FILE *file);

void graphVizAddInitialState(FILE *file, int q);

void graphVizAddFinalState(FILE *file, int q);

void graphVizAddTransition(FILE *file, int q1, char symbol, int q2);

void graphVizEnd(FILE *file);

#endif