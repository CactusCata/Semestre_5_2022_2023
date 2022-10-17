#ifndef GRAPH_LIST_ADJ_H
#define GRAPH_LIST_ADJ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "utils.h"

typedef struct {
  unsigned int edgeAmount;
  Stack *listAdj;
} GraphL;

GraphL initGraphL(unsigned int edgeAmount);
// Initialise un graph sans connexion d'ordre edgeAmount

GraphL initGraphLFromFile(char *fileName);
// Génère un graph depuis un fichier

void writeGraphLInFile(GraphL graph, char *fileName);
// Serialize un graph dans un fichier

void freeGraphL(GraphL graph);
// Libère la mémoire du graph correspondant

void printGraphL(GraphL graph);
// Ecrit sur la console le graph correspondant

void drawGraphL(GraphL graph, char *path, char *fileName);
// Créer un fichier .png à partir du graph correspondant

size_t getComposanteConnexeAmountRecL(GraphL graph);
// Calcul le nombre de composante connexe du graph correspondant

void reachAllNeighborsRecL(size_t s, GraphL graph, unsigned char *reached);
// Permet de visiter tous les voisins dans une composante connexe du graph correspondant

size_t getComposanteConnexeAmountIteL(GraphL graph);
// Calcul le nombre de composante connexe du graph correspondant

void reachAllNeighborsIteL(size_t s, GraphL graph, unsigned char *reached);
// Permet de visiter tous les voisins dans une composante connexe du graph correspondant

#endif
