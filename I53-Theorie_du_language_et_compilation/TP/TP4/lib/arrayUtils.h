#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdio.h>
#include "utils.h"

bool intIsInArray(int value, int *array, size_t arraySize);

void fillIntArray(int *array, size_t arraySize, int value);

void shiftValuesArrayToRight(int *array, int arraySize, int startShiftingIndex);

void printArray(int *array, size_t arraySize);

#endif
