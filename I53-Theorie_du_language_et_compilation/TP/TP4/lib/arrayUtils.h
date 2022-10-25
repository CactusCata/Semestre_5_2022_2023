#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdio.h>
#include "utils.h"

bool intIsInArray(int value, int *array, size_t arraySize);

void fillIntArray(int *array, size_t arraySize, int value);

void fillCharArray(char *array, size_t arraySize, char value);

void printArrayStopValue(int *array, int stopValue);

void shiftValuesArrayToRight(int *array, int arraySize, int startShiftingIndex);

void printArray(int *array, size_t arraySize);

bool TwoDArrayIsInThreeDArray(int *array2D, int **array3D, int size3DArray, int *index);

void print3DArrayStopValue(int **array, int size, int stopValue);

void fill3DArrayWithNull(int **array3D, int arraySize);

int *ajustArray(int *from, int size);

int getArraySize(int *array, int stopValue);

#endif
