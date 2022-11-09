#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

//bool intIsInArray(int value, int *array, size_t arraySize);

bool charArrayContrains(char *array, int arraySize, char value);

int *copyArray(int *array, int arraySize);

char *copyCharArray(char *array, int arraySize);

void fillIntArray(int *array, size_t arraySize, int value);

void fillCharArray(char *array, size_t arraySize, char value);

//void printArrayStopValue(int *array, int stopValue);

void shiftValuesArrayToRight(int *array, int arraySize, int startShiftingIndex);

char *serializeArray(int *array, int arraySize);

char *serializeSet(int *array, int arraySize);

char *serializeContainer(int *array, int arraySize, char bracketTypeLeft, char bracketTypeRight);

void printArrayChar(char *array, int arraySize);

void printArray(int *array, size_t arraySize);

//bool TwoDArrayIsInThreeDArray(int *array2D, int **array3D, int size3DArray, int *index);

//void print3DArrayStopValue(int **array, int size, int stopValue);

//void fill3DArrayWithNull(int **array3D, int arraySize);

int *ajustArray(int *from, int size);

//int getArraySize(int *array, int stopValue);

void concatenateArrays(int *stateReached, int *tmp, int arraySize);

void printMatrix(char ***textMatrix, int **dimsMatrix, int lineAmount, int colAmount);

void sortArray(int *array, int arraySize);

char *unionCharArray(char *array1, int arraySize1, char *array2, int arraySize2);

#endif
