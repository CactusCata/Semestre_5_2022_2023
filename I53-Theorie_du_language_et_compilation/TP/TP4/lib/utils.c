#include "utils.h"

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

int *getAllIntInLine(char *line, int sizeArray) {
  int *numbers = (int *) malloc(sizeof(int) * sizeArray);
  int lastNumber = -1;
  unsigned int cursor = 0;
  unsigned int index = 0;
  while ((lastNumber = getNextIntFromLine(line, &cursor)) != -1) {
    numbers[index] = lastNumber;
    index++;
    cursor++; // add space character
  }
  return numbers;
}
