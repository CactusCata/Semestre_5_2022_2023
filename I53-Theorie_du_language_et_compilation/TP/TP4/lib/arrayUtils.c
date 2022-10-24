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

void fillCharArray(char *array, size_t arraySize, char value) {
  for (size_t i = 0; i < arraySize; i++) {
    array[i] = value;
  }
}

int getArraySize(int *array, int stopValue) {
  int count = 0;
  for (; array[count] != stopValue; count++);
  return count;
}

void shiftValuesArrayToRight(int *array, int arraySize, int startShiftingIndex) {
  for (int i = arraySize - 2; i >= startShiftingIndex; i--) {
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

void printArrayStopValue(int *array, int stopValue) {
  printArray(array, getArraySize(array, stopValue));
}

bool TwoDArrayIsInThreeDArray(int *array2D, int size2DArray, int **array3D, int size3DArray) {
  for (int i = 0; i < size3DArray && array3D[i] != NULL; i++) {
    int *currentArray = array3D[i];
    bool match = True;
    for (int j = 0; j < size2DArray; j++) {
      if (array2D[j] != currentArray[j]) {
        match = False;
        break;
      }
    }
    if (match) {
      return True;
    }
  }
  return False;
}

void fill3DArrayWithNull(int **array3D, int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    array3D[i] = NULL;
  }
}

int *ajustArray(int *from, int size) {
  int *to = (int *) malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    to[i] = from[i];
  }
  free(from);
  return to;
}
