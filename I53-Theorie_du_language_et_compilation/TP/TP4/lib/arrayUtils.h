#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdio.h>
#include "utils.h"

bool intIsInArray(int value, int *array, size_t arraySize);

void fillIntArray(int *array, size_t arraySize, int value);

void shiftValuesArrayToRight(int *array, int arraySize, int startShiftingIndex);

void printArray(int *array, size_t arraySize);

bool TwoDArrayIsInThreeDArray(int *array2D, int size2DArray, int **array3D, int size3DArray);

void fill3DArrayWithNull(int **array3D, int arraySize);

int *ajustArray(int *from, int size);

#endif
