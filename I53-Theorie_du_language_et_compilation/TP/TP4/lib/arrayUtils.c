#include "arrayUtils.h"

bool intIsInArray(int value, int *array, size_t arraySize) {
  for (size_t i = 0; i < arraySize; i++) {
    if (array[i] == value) {
      return True;
    }
  }
  return False;
}

void fillIntArray(int *array, size_t arraySize, int value) {
  for (size_t i = 0; i < arraySize; i++) {
    array[i] = value;
  }
}

void shiftValuesArrayToRight(int *array, int arraySize, int startShiftingIndex) {
  for (int i = arraySize - 1; i >= startShiftingIndex; i--) {
    array[i + 1] = array[i];
  }
}

void printArray(int *array, size_t arraySize) {
  printf("[");
  if (arraySize > 0) {
    for (size_t i = 0; i < arraySize - 1; i++) {
      printf("%d, ", array[i]);
    }
    printf("%d", array[arraySize - 1]);
  }
  printf("]\n");
}