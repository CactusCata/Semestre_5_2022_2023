#ifndef VECT_H
#define VECT_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "arrayUtils.h"

// Les valeurs de array doivent être triées dans l'ordre croissante et terminer par un -1
typedef struct Vect {
    int *array;
    int realSize;
    int size;
    bool needSorted;
} Vect, *VectPtr;

// Crée un vecteur de taille 1 contenant la valeur -1
Vect *createVect(bool needShorted);

// Crée un vecteur à partir d'un tableau pas forcément trié
Vect *createVectFromIntArray(int *array, int arraySize, bool needShorted);

// Libère la mémoire du vecteur
void freeVect(Vect *vect);

// Renvoie vrai si le vecteur est vide
bool vectIsEmpty(Vect *vect);

// Ajoute un élément dans vect
void vectAdd(Vect *vect, int value);

void vectAddAll(Vect *vect, int *array, int arraySize);

// Do not use this function if Vect is sorted
void vectSet(Vect *vect, int value, int index);

// Permet de déterminer à quel indice la valeur value serait placée de la façon la plus appropriée 
int getBestVectIndex(Vect *vect, int value);

// Renvoie vrai si le vecteur contient la valeur 'value'
bool vectContrainsValue(Vect *vect, int value);

// Augmente la taille du vecteur de size cases
void expendVectSize(Vect *vect, int size);

// Calcul l'occurence des valeurs identiques entre deux vecteurs
int sameValuesOccurenciesInVect(Vect *v1, Vect *v2);

// Fusionne deux vecteurs et ne recopie pas les valeurs déjà présentes de l'un dans l'autre
void unionVectAsSet(Vect *v1, Vect *v2);

// Renvoie vrai si l'intersection des deux vecteurs n'est pas vide. Sinon renvoie faux
bool intersectionOfVectIsNotEmpty(Vect *v1, Vect *v2);

// Renvoie sous chaine de caractère le vecteur
char *serializeVect(Vect *vect);

// Renvoie sous chaine de caractère le vecteur avec les valeurs -1
char *serializeRealVect(Vect *vect);

// Affiche le vecteur sous la forme serializeRealVect
void printVect(Vect *vect);

// Affiche le tableau associé au vecteur
void printVectArray(Vect *vect);

// Renvoie la chaine de caractère associée au Vect
char *serializeVectArray(Vect *vect);

// Converti un Vecteur en tableau d'entier
int *vectToIntArray(Vect *vect);

// Converti un tableau d'entier en vecteur avec comme valeur de fin de lecture stopValue
Vect *intArrayToVect(int *array, int stopValue);

// Renvoie la valeur à l'indice index
int vectGet(Vect *vect, int index);

// Renvoie vrai si les vecteurs sont les mêmes
bool vectEqualsToVect(Vect *v1, Vect *v2);

// Crée une copie de vect
Vect *vectCopy(Vect *vect);

#endif