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

Graph init(const unsigned int &n);

Graph readGraph(const std::string &fileName);

void printGraph(const Graph &g);

unsigned int getConnexeComposantesAmount(const Graph &g);

void reachNeighbor(const unsigned int &s, const Graph &g);

bool isConnexe(const Graph &g);

bool isEulerien(const Graph &g);

#endif