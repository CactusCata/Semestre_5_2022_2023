#ifndef GRAPH_LIST_ADJ_H
#define GRAPH_LIST_ADJ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "stack.h"
#include "utils.h"
#include "graphUtils.h"

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

unsigned char isConnexe(GraphL graph);
// Renvoie 1 si le graph est connexe, 0 sinon

unsigned int proportionConnexe(int order);
// Renvoie le nombre de graph connexe pour tous les graphs
// d'ordre ordre

GraphL intToGraph(unsigned int n, int order, Pair *pairs);
// Converti un nombre en graph
// La variable pair vaut generatePairEnum(int order)

void reachAllNeighborsRecLAndRecord(unsigned int s, GraphL graph, unsigned char *reached, unsigned int *sizeComposante);
// Atteint tous les sommets d'une composante connexe et enregistre
// le nombre de sommet de la composante analysée

unsigned int geante(GraphL graph);
// Renvoie la taille de la plus grande composante connexe

unsigned int getDegree(GraphL graph, unsigned int sommet);
// Renvoie le degré d'un sommet

InfoGraph *getInfosGraph(GraphL graph, int *sizeInfoGraph);
// Renvoie un tableau de couple (representant, taille de la composante)

void Eulerien(GraphL graph, int s);
// Affiche à l'écran un chemin eulérien

Stack *promenade(GraphL graph, int s);

GraphL randomGraph(int n, float p);

#endif
