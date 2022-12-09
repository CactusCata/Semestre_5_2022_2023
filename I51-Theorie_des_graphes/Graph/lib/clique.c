#include "clique.h"

void getMaximumClique(GraphM *g) {

  for (int i = 0; i < g->edgeAmount; i++) {
    int *currentList = malloc(sizeof(int) * g->edgeAmount);
    int currentListCursor = 0;
    int *blackList = malloc(sizeof(int) * g->edgeAmount);
    int blackListCursor = 0;

    for (int i = 0; i < g->edgeAmount; i++) {
      currentList[i] = 0;
      blackList[i] = 0;
    }

    currentList[i] = 1;

    getMaximalClique(g, currentList, &currentListCursor, blackList, &blackListCursor);
    //printf("(%d) Taille de la liste: %d\n", i, getCliqueSize(currentList, g->edgeAmount));
    printArray(currentList, g->edgeAmount);
  }

}

int *genPerm(int n) {
  int *perm = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    perm[i] = i;
  }

  for(int i = 0; i < n; i++) {
    j = rand() % (n - i) + i;
    tmp = perm[i];
    perm[i] = perm[j];
    perm[j] = tmp;
  }

  return perm
}

int getCliqueSize(int *array, int arraySize) {
  int amount = 0;
  for (int i = 0; i < arraySize; i++) {
    if (array[i]) amount++;
  }
  return amount;
}


void getMaximalClique(GraphM *g, int *currentList, int *currentListCursor, int *blackList, int *blackListCursor) {
  for (int i = 0; i < g->edgeAmount && !blackList[i]; i++) { // i est le sommet choisi, il faut qu'il soit dispo et pas dans la blacklist
    int good = 1;
    for (int j = 0; j < g->edgeAmount && good; j++) { // on regarde tous les sommets dans la currentlist
      if (currentList[j]) {
        if (!g->matrixAdj[i][j]) { // si i et j ne sont pas connectés, alors on annule
          good = 0;
        }
      }
    }
    if (good) {
      currentList[i] = 1;
      blackList[i] = 1;
    }
  }
}

/*
void getMaximalClique(GraphM *g, int *currentList, int *currentListCursor, int *blackList, int *blackListCursor) {
  for (int i = 0; i < g->edgeAmount && !blackList[i]; i++) { // i est le sommet choisi, il faut qu'il soit dispo et pas dans la blacklist
    int good = 1;
    for (int j = 0; j < g->edgeAmount && good; j++) { // on regarde tous les sommets dans la currentlist
      if (currentList[j]) {
        if (!g->matrixAdj[i][j]) { // si i et j ne sont pas connectés, alors on annule
          good = 0;
        }
      }
    }
    if (good) {
      currentList[i] = 1;
      blackList[i] = 1;
    }
  }
}
*/
