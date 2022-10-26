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

void print3DArrayStopValue(int **array, int size, int stopValue) {
  for (int i = 0; i < size; i++) {
    if (array[i] != NULL)
      printArrayStopValue(array[i], stopValue);
    else
      break;
  }
}

bool TwoDArrayIsInThreeDArray(int *array2D, int **array3D, int size3DArray, int *index) {
  int arraySize2D = getArraySize(array2D, -1);
  printf("\n\nComparaison 3D\n");
  printf("Cible: \n");
  printf("Taille : %d\n", getArraySize(array2D, -1));
  printArrayStopValue(array2D, -1);
  printf("\nCurrent: \n");
  print3DArrayStopValue(array3D, size3DArray, -1);

  if (arraySize2D == 0) {
    for (int i = 0; i < size3DArray && array3D[i] != NULL; i++) {
      int *currentArray = array3D[i];
      if (getArraySize(currentArray, -1) == 0) {
        (*index) = i;
        return True;
      }
    }
    return False;
  }

  for (int i = 0; i < size3DArray && array3D[i] != NULL; i++) {
    int *currentArray = array3D[i];
    bool match = True;
    int currentArraySize = getArraySize(currentArray, -1);

    for (int j = 0; j < arraySize2D; j++) {
      if (array2D[j] != currentArray[j]) {
        match = False;
        break;
      }
    }

    if (match && (arraySize2D == currentArraySize)) {
      printf("Add\n");
      (*index) = i;
      return True;
    }
  }
  printf("Not append\n");
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

void concatenateArrays(int *stateReached, int *tmp, int arraySize) {
  /**
    tmp doit être trié dans l'ordre croissant et remplis de -1 après
  */

  int stateReachedCursor = 0;
  int tmpCursor = 0;
  while (tmp[tmpCursor] != -1) {
    if ((tmp[tmpCursor] < stateReached[stateReachedCursor]) || (stateReached[stateReachedCursor] == -1)) {
      shiftValuesArrayToRight(stateReached, arraySize, stateReachedCursor);
      stateReached[stateReachedCursor] = tmp[tmpCursor];
      stateReachedCursor++;
      tmpCursor++;
    } else if (tmp[tmpCursor] == stateReached[stateReachedCursor]) {
      tmpCursor++;
      stateReachedCursor++;
    } else {
      tmpCursor++;
    }
    printf("tmpCusor = %d\n", tmpCursor);
    printf("stateReachedCursor = %d\n", stateReachedCursor);
  }

}
