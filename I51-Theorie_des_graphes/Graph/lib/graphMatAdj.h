#ifndef GRAPH_MAT_ADJ_H
#define GRAPH_MAT_ADJ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int edgeAmount;
  unsigned char **matrixAdj;
} GraphM;

GraphM initGraphM(unsigned int edgeAmount);
// Initialise un graph sans connexion d'ordre edgeAmount

GraphM initGraphMFromFile(char *fileName);
// Génère un graph depuis un fichier

void writeGraphMInFile(GraphM graph, char *fileName);
// Serialize un graph dans un fichier

void freeGraphM(GraphM graph);
// Libère la mémoire du graph correspondant

void printGraphM(GraphM graph);
// Ecrit sur la console le graph correspondant

void drawGraphM(GraphM graph, char *path, char *fileName);
// Créer un fichier .png à partir du graph correspondant

size_t getComposanteConnexeAmountM(GraphM graph);
// Calcul le nombre de composante connexe du graph correspondant

void reachAllNeighborsM(size_t s, GraphM graph, unsigned char *reached);
// Permet de visiter tous les voisins dans une composante connexe du graph correspondant

#endif
