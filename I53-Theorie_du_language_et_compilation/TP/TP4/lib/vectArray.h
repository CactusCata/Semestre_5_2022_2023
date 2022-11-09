#ifndef VECT_ARRAY_H
#define VECT_ARRAY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#include "vect.h"

typedef struct VectArray {
    int size;
    int realSize;
    Vect **array;
} VectArray;

VectArray *createVectArray();

// Ne free pas les *Vect, seulement le tableau qui les contient et le pointeur de VectArray
void freeVectArray(VectArray *vectArray);

void vectArrayAdd(VectArray *vectArray, Vect *vect);

void vectArraySet(VectArray *vectArray, Vect *vect, int index);

// Augmente la taille du vecteur de size cases
void expendVectArraySize(VectArray *vectArray, int size);

Vect *vectArrayGet(VectArray *vectArray, int index);

// Renvoie l'indice du vecteur dans vectArray s'il s'y trouve. Renvoie -1 sinon
int getIndexOfVectInVectArray(VectArray *vectArray, Vect *vect);

bool vectIsInVectArray(VectArray *vectArray, Vect *vect);

#endif