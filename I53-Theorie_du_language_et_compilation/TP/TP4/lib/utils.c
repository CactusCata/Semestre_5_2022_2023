#include "utils.h"

/**
 * @brief Détermine le prochain entier sur une chaine de caractère. 
 * 
 * @param lineBuffer chaine de cractère à analyser
 * @param cursor position du début de la lecture
 * @return int la valeur de l'entier lu s'il existe, -1 sinon
 */
int getNextIntFromLine(char *lineBuffer, unsigned int *cursor) {
  if (lineBuffer[*cursor] > '9' || lineBuffer[*cursor] < '0') {
    return -1;
  }

  int res = 0;
  while ((lineBuffer[*cursor] <= '9') && (lineBuffer[*cursor] >= '0')) {
    res *= 10;
    res += lineBuffer[*cursor] - '0';
    (*cursor)++;
  }
  return res;
}

/**
 * @brief Renvoie tous les entiers contenus dans une chaine de caractère.
 * Le format de la ligne donnée en paramètre doit être: %d %d %d %d %d etc...
 * I.e. avec un espace entre chaque nombre
 * 
 * @param line ligne à analyser
 * @param sizeArray taille de la liste de nombre
 * @return int* le tableau de tous les entiers lus dans la chaine de caractère
 */
int *getAllIntInLine(char *line, int sizeArray) {
  int *numbers = (int *) malloc(sizeof(int) * sizeArray);
  int lastNumber = -1;
  unsigned int cursor = 0;
  unsigned int index = 0;
  while ((lastNumber = getNextIntFromLine(line, &cursor)) != -1 && (index < sizeArray)) {
    numbers[index] = lastNumber;
    index++;
    cursor++; // add space character
  }
  return numbers;
}

/**
 * @brief Ajoute une chaine de caractère à une autre.
 * Place le caractère de contrôle '\0' en fin de ligne.
 * 
 * @param base chaine de caractère qui recevra une chaine de caractère
 * @param toAdd chaine de caractère qui sera ajoutée
 * @param indexStartToWrite indice à partir du quel il faut écrire
 */
void appendText(char *base, char *toAdd, int *indexStartToWrite) {
  int i = 0;
  for (; toAdd[i] != '\0'; i++) {
    base[*indexStartToWrite + i] = toAdd[i];
  }
  base[*indexStartToWrite + i] = '\0';
  (*indexStartToWrite) += i;
}

/**
 * @brief Ecrit n fois un cractère dans une chaine de cractère à partir d'un indice.
 * Ne place pas le cractère de contrôle '\0' à la fin de l'écriture.
 * 
 * @param text texte dans lequel il faut écrire, doit avoir la place d'écrire le caractère n fois
 * @param startWrittingIndex indice à partir duquel il faut commencer à écrire
 * @param c le caractère à répeter
 * @param times le nombre de fois qu'il faut l'écrire
 */
void writeNTimes(char *text, int *startWrittingIndex, char c, int times) {
  for (int i = 0; i < times; i++) {
    text[*startWrittingIndex + i] = c;
  }
  *startWrittingIndex = *startWrittingIndex + times;
}

/**
 * @brief Arrête le programme si un malloc n'est pas permis
 * 
 * @param condition si condition, alors déclarer l'exception
 */
void throwMallocErrorIfTrue(bool condition) {
  if (condition) {
    printf("Can't malloc...\n");
    printf("Exit program\n");
    exit(1);
  }
}