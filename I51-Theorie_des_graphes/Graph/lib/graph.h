#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int edgeAmount;
  unsigned char **matrixAdj;
} Graph;

Graph initGraph(unsigned int edgeAmount);
// Initialise un graph sans connexion d'ordre edgeAmount

void freeGraph(Graph graph);
// Libère la mémoire du graph correspondant

void printGraph(Graph graph);
// Ecrit sur la console le graph correspondant

void drawGraph(Graph graph, char *path, char *fileName);
// Créer un fichier .png à partir du graph correspondant

size_t getComposanteConnexeAmount(Graph graph);
// Calcul le nombre de composante connexe du graph correspondant

void reachAllNeighbors(size_t s, Graph graph, unsigned char *reached);
// Permet de visiter tous les voisins dans une composante connexe du graph correspondant

#endif
