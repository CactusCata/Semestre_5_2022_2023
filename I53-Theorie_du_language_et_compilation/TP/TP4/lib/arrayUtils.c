#include "arrayUtils.h"


/**
 * @brief Détermine si un entier est contenu dans tableau
 * 
 * @param value entier à rechercher
 * @param array tableau
 * @param arraySize taille du tableau 
 * @return true si value est contenu dans le tableau
 * @return false si value n'est pas contenu dans le tableau
 */
/*
bool intIsInArray(int value, int *array, size_t arraySize) {
  for (size_t i = 0; i < arraySize; i++) {
    if (array[i] == value) {
      return true;
    }
  }
  return false;
}
*/

/**
 * @brief Détermine si un caractère est contenu dans tableau
 * 
 * @param array tableau
 * @param arraySize taille du tableau 
 * @param value caractère à rechercher
 * @return true si value est contenu dans le tableau
 * @return false si value n'est pas contenu dans le tableau
 */
bool charArrayContrains(char *array, int arraySize, char value) {
  for (int i = 0; i < arraySize; i++) {
    if (array[i] == value) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Recopie le contenu d'un tableau
 * 
 * @param array tableau à recopier
 * @param arraySize taille du tableau à recopier
 * @return int* le tableau copié
 */
int *copyArray(int *array, int arraySize) {
  int *arrayCopy = (int *) malloc(sizeof(int) * arraySize);
  throwMallocErrorIfTrue(arrayCopy == NULL);
  for (int i = 0; i < arraySize; i++) {
    arrayCopy[i] = array[i];
  }
  return arrayCopy;
}

/**
 * @brief Recopie le contenu d'un tableau
 * 
 * @param array tableau à recopier
 * @param arraySize taille du tableau à recopier
 * @return char* le tableau recopié
 */
char *copyCharArray(char *array, int arraySize) {
  char *arrayCopy = (char *) malloc(sizeof(char) * arraySize);
  throwMallocErrorIfTrue(arrayCopy == NULL);
  for (int i = 0; i < arraySize; i++) {
    arrayCopy[i] = array[i];
  }
  return arrayCopy;
}

/**
 * @brief Rempli un tableau d'entier d'une valeur
 * 
 * @param array le tableau à remplir
 * @param arraySize la taille du tableau à remplir
 * @param value la valeur à placer dans tous les indices du tableau
 */
void fillIntArray(int *array, size_t arraySize, int value) {
  for (size_t i = 0; i < arraySize; i++) {
    array[i] = value;
  }
}

/**
 * @brief Rempli un tableau de caractère d'une valeur
 * 
 * @param array le tableau à remplir
 * @param arraySize la taille du tableau à remplir
 * @param value la valeur à placer dans tous les indices du tableau
 */
void fillCharArray(char *array, size_t arraySize, char value) {
  for (size_t i = 0; i < arraySize; i++) {
    array[i] = value;
  }
}

/**
 * @brief Renvoie la taille du tableau en supposant qu'il se termine par la valeur stopValue
 * 
 * @param array Le tableau dont on veut connaître la taille
 * @param stopValue La valeur corresponsant à la fin du tableau
 * @return int la taille du tableau
 */
/*
int getArraySize(int *array, int stopValue) {
  int count = 0;
  for (; array[count] != stopValue; count++);
  return count;
}
*/

/**
 * @brief Provoque un décalage d'une unité des valeurs d'un tableau à droite
 * 
 * @param array tableau
 * @param arraySize taille du tableau
 * @param startShiftingIndex indice à partir du quel il faut décaler les indices
 */
void shiftValuesArrayToRight(int *array, int arraySize, int startShiftingIndex) {
  if (arraySize - 2 >= 0) {
    for (int i = arraySize - 2; i >= startShiftingIndex; i--) {
      array[i + 1] = array[i];
    }
  }
}

/**
 * @brief Converti un tableau en chaine de caractère.
 * Pensez à free la chaine de caractère après utilisation
 * 
 * @param array tableau à convertir
 * @param arraySize taille du tableau à convertir
 * @param bracketTypeLeft caractère encadrant la liste à gauche
 * @param bracketTypeRight caractère encadrant la liste à droite
 * @return char* la chaine de caractère corresponsant au tableau
 * 
 */
char *serializeContainer(int *array, int arraySize, char bracketTypeLeft, char bracketTypeRight) {
  char *text = (char *) malloc(sizeof(char) * 2048);
  throwMallocErrorIfTrue(text == NULL);
  int textCursorW = 0;
  text[textCursorW++] = bracketTypeLeft;
  if (arraySize > 0) {
    char numberBuffer[20];
    for (size_t i = 0; i < arraySize - 1; i++) {
      sprintf(numberBuffer, "%d, ", array[i]);
      appendText(text, numberBuffer, &textCursorW);
    }
    sprintf(numberBuffer, "%d", array[arraySize - 1]);
    appendText(text, numberBuffer, &textCursorW);
  }
  text[textCursorW++] = bracketTypeRight;
  text[textCursorW++] = '\0';
  return text;
}

/**
 * @brief Converti un tableau en chaine de caractère avec comme
 * caractère encadrant '[' et ']'.
 * Pensez à free la chaine de caractère après utilisation
 * 
 * @param array tableau à convertir
 * @param arraySize taille du tableau à convertir
 * @return char* la chaine de caractère corresponsant au tableau
 */
char *serializeArray(int *array, int arraySize) {
  return serializeContainer(array, arraySize, '[', ']');
}

/**
 * @brief Converti un tableau en chaine de caractère avec comme
 * caractère encadrant '{' et '}'.
 * Pensez à free la chaine de caractère après utilisation
 * 
 * @param array tableau à convertir
 * @param arraySize taille du tableau à convertir
 * @return char* la chaine de caractère corresponsant au tableau
 */
char *serializeSet(int *array, int arraySize) {
  return serializeContainer(array, arraySize, '{', '}');
}

/**
 * @brief Ecrit dans la sortie standard un tableau d'entier.
 * 
 * @param array tableau d'entier à écrire
 * @param arraySize taille du tableau à écrire
 */
void printArray(int *array, size_t arraySize) {
  char *arraySerialized = serializeArray(array, arraySize);
  printf("%s", arraySerialized);
  free(arraySerialized);
}

/**
 * @brief Ecrit dans la sortie standard un tableau de caractère.
 * 
 * @param array tableau de caractère à imprimer
 * @param arraySize taille du tableau 
 */
void printArrayChar(char *array, int arraySize) {
  printf("[");
  if (arraySize > 0) {
    for (size_t i = 0; i < arraySize - 1; i++) {
      printf("'%c', ", array[i]);
    }
    printf("'%c'", array[arraySize - 1]);
  }
  printf("]");
}

/**
 * @brief Ecrit dans la sortie standard un tableau d'entier dont on ne connais pas
 * la taille mais seulement la dernière valeur qui est une valeur de contrôle.
 * 
 * @param array tableau à afficher
 * @param stopValue valeur de contrôle
 */
/*
void printArrayStopValue(int *array, int stopValue) {
  printArray(array, getArraySize(array, stopValue));
}
*/

/**
 * @brief Ecrit dans la sortie standard un tableau à deux dimensions.
 * 
 * @param array tableau à deux dimensions
 * @param size nombre de ligne du tableau à deux dimensions
 * @param stopValue valeur contrôle pour la fin de lecture des lignes de la matrice
 */
/*
void print3DArrayStopValue(int **array, int size, int stopValue) {
  for (int i = 0; i < size; i++) {
    if (array[i] != NULL)
      printArrayStopValue(array[i], stopValue);
    else
      break;
  }
}
*/

/**
 * @brief Détermine si un tableau à une dimension appartient à un tableau à deux dimensions 
 * 
 * @param array2D tableau à une dimensions à rechercher
 * @param array3D tableau à deux dimensions à fouiller
 * @param size3DArray taille du tableau à deux dimensions
 * @param index indice de array2D dans array3D s'il s'y trouve. Sinon -1 
 * @return true si array2D se trouve dans array3D
 * @return false si array2D ne se trouve pas dans array3D
 */
/*
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
        return true;
      }
    }
    return false;
  }

  for (int i = 0; i < size3DArray && array3D[i] != NULL; i++) {
    int *currentArray = array3D[i];
    bool match = true;
    int currentArraySize = getArraySize(currentArray, -1);

    for (int j = 0; j < arraySize2D; j++) {
      if (array2D[j] != currentArray[j]) {
        match = false;
        break;
      }
    }

    if (match && (arraySize2D == currentArraySize)) {
      printf("Add\n");
      (*index) = i;
      return true;
    }
  }
  printf("Not append\n");
  return false;
}
*/

/**
 * @brief Rempli un tableau 2D de valeur NULL.
 * 
 * @param array3D tableau 2D à remplir
 * @param arraySize taille du tableau 2D
 */
/*
void fill3DArrayWithNull(int **array3D, int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    array3D[i] = NULL;
  }
}
*/

/**
 * @brief Permet de réajuster un malloc pour en diminuer la taille.
 * Attention, la variable from est free après appel de cette fonction
 * 
 * @param from tableau à réadapter
 * @param size taille du nouveau tableau
 * @return int* nouveau tableau réajusté
 */
int *ajustArray(int *from, int size) {
  int *to = (int *) malloc(sizeof(int) * size);
  throwMallocErrorIfTrue(to == NULL);
  for (int i = 0; i < size; i++) {
    to[i] = from[i];
  }
  free(from);
  return to;
}

/**
 * @brief Permet d'inserer toutes les valeurs du tableau array2 dans array1
 * 
 * @param array1 tableau d'entier trié dans l'ordre croissant terminant par un -1
 * @param array2 tableau d'entier trié dans l'ordre croissant terminant par un -1
 * @param arraySize taille de array1
 */
/*
void concatenateArrays(int *array1, int *array2, int arraySize) {
  int array1Cursor = 0;
  int array2Cursor = 0;
  while (array2[array2Cursor] != -1 && (array1Cursor < arraySize)) {
    if ((array2[array2Cursor] < array1[array1Cursor]) || (array1[array1Cursor] == -1)) {
      shiftValuesArrayToRight(array1, arraySize, array1Cursor);
      array1[array1Cursor] = array2[array2Cursor];
      array1Cursor++;
      array2Cursor++;
    } else if (array2[array2Cursor] == array1[array1Cursor]) {
      array2Cursor++;
      array1Cursor++;
    } else {
      array2Cursor++;
    }
  }

}
*/


/**
 * @brief Ecrit sur la sortie standard une matrice dans le format suivant:
 * 
 * +-------+-------+-----+---------+
 * | Delta |   &   |  a  |    b    |
 * +-------+-------+-----+---------+
 * |  {0}  | {0,1} | {0} | {0,1,3} |
 * +-------+-------+-----+---------+
 * | {0,1} |  {0}  | {1} |   {0}   |
 * +-------+-------+-----+---------+
 * 
 * @param textMatrix matrice des chaines à afficher
 * @param dimsMatrix longueue des chaines à afficher
 * @param lineAmount nombre de ligne de la matrice
 * @param colAmount nombre de colonne de la matrice
 */
void printMatrix(char ***textMatrix, int **dimsMatrix, int lineAmount, int colAmount) {
  int *colsLengths = calloc(colAmount, sizeof(int));
  throwMallocErrorIfTrue(colsLengths == NULL);

  for (int line = 0; line < lineAmount; line++) {
    for (int col = 0; col < colAmount; col++) {
      int currentSize = dimsMatrix[line][col];
      int actualMaxSize = colsLengths[col];
      if (currentSize > actualMaxSize) {
        colsLengths[col] = currentSize;
        if ((colsLengths[col] & 1) == 0) {
          colsLengths[col]++;
        }
      }
    }
  }

  // Write the matrix
  int matrixTextWidth = 1; // First '+'
  for (int i = 0; i < colAmount; i++) {
    matrixTextWidth += 2 + colsLengths[i] + 1 + 1 + 1; // 2: space char on left and right, 1: '+' character, 1: '\n' char, 1: '\0' char
  }

  char *delimiterLine = (char *) malloc(sizeof(char) * matrixTextWidth);
  throwMallocErrorIfTrue(delimiterLine == NULL);
  
  // Build delimiter line
  int delimiterLineCursor = 0;
  delimiterLine[delimiterLineCursor++] = '+';
  for (int i = 0; i < colAmount; i++) {
    writeNTimes(delimiterLine, &delimiterLineCursor, '-', 2 + colsLengths[i]);
    delimiterLine[delimiterLineCursor++] = '+';
  }
  delimiterLine[delimiterLineCursor++] = '\0';


  puts(delimiterLine);

  for (int line = 0; line < lineAmount; line++) {
    char *lineTextMatrix = (char *) malloc(sizeof(char) * matrixTextWidth); 
    throwMallocErrorIfTrue(lineTextMatrix == NULL);
    int lineTextMatrixCursor = 0;
    lineTextMatrix[lineTextMatrixCursor++] = '|';
    for (int col = 0; col < colAmount; col++) {
      int spaceCharNeeded = (colsLengths[col] - dimsMatrix[line][col] + 2) / 2;

      writeNTimes(lineTextMatrix, &lineTextMatrixCursor, ' ', spaceCharNeeded);
      appendText(lineTextMatrix, textMatrix[line][col], &lineTextMatrixCursor);

      if ((colsLengths[col] & 1) != (dimsMatrix[line][col] & 1)) {
        writeNTimes(lineTextMatrix, &lineTextMatrixCursor, ' ', spaceCharNeeded + 1);
      } else {
        writeNTimes(lineTextMatrix, &lineTextMatrixCursor, ' ', spaceCharNeeded);
      }

      lineTextMatrix[lineTextMatrixCursor++] = '|';
    }
    lineTextMatrix[lineTextMatrixCursor++] = '\0';
    puts(lineTextMatrix);
    free(lineTextMatrix);
    puts(delimiterLine);
  }

  free(colsLengths);
  free(delimiterLine);

}

/**
 * @brief Tri un tableau d'entier. La méthode de tri est le tri par séléction.
 * 
 * @param array tableau d'entier
 * @param arraySize taille du tableau à trier
 */
void sortArray(int *array, int arraySize) {
  for (int i = 0; i < arraySize - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < arraySize; j++) {
      if (array[j] < array[minIndex]) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      int cached = array[i];
      array[i] = array[minIndex];
      array[minIndex] = cached;
      
    }
  }
}

/**
 * @brief Calcul la réunion de deux tableaux de caracteres. Ne modifie pas les tableaux.
 * 
 * @param array1 tableau de caractère
 * @param arraySize1 taille du tableau array1
 * @param array2 tableau de caractère
 * @param arraySize2 taille du tableau array2
 * @return char* reunion des deux tableaux de caractères.
 */
char *unionCharArray(char *array1, int arraySize1, char *array2, int arraySize2) {
  char *unionArray = (char *) malloc(sizeof(char) * (arraySize1 + arraySize2 + 1));
  int cursor = 0;

  // Add array1 content
  for (int i = 0; i < arraySize1; i++) {
    unionArray[cursor++] = array1[i];
  }

  // Add array2 content
  for (int i = 0; i < arraySize2; i++) {
    if (!charArrayContrains(unionArray, arraySize1, array2[i])) {
      unionArray[cursor++] = array2[i];
    }
  }

  unionArray[cursor++] = '\0';

  char *resizedUnionArray = copyCharArray(unionArray, cursor);
  free(unionArray);

  return resizedUnionArray;
}