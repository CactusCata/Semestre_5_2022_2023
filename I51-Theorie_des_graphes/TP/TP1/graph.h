#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    false,
    true
} boolean;

typedef struct {
    boolean **matrixAdj;
    unsigned int order;
} Graph;

Graph initGraph(unsigned int order);
void deleteGraph(Graph g);
Graph readGraph(char *fileName);
void writeGraph(Graph g);
void writeGraph2(Graph g);
void printGraph(Graph g);
void drawGraph(Graph g);


#endif