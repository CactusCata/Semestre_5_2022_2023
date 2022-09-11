#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <errno.h>
#include <stdio.h>

typedef struct {
    unsigned int ordre;
    char **matriceAdjacence;
} Graph;

Graph init(unsigned int n);

Graph readGraph(std::string fileName);

void printGraph(Graph g);

int getConnexeComposantesAmount(Graph g);

void reachNeighbor(int s, Graph g);

#endif