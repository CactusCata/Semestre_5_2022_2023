#include "utils.h"

int readNextUInt(char *text, size_t *start) {
  if ('0' > text[*start] || text[*start] > '9') {
    return -1;
  }

  int res = 0;
  while ('0' <= text[*start] && text[*start] <= '9') {
    res *= 10;
    res += text[*start] - '0';
    (*start)++;
  }
  return res;
}

char *intToStr(int value) {
  int valueCopy = value;
  size_t charSize = 1;
  while (valueCopy > 9) {
    valueCopy /= 10;
    charSize++;
  }

  char *text = (char *) malloc(sizeof(char) * (charSize + 1));
  sprintf(text, "%d", value);
  text[charSize] = '\0';
  return text;
}

void appendText(char *base, size_t *cursor, char *toAdd) {
  size_t i = 0;
  for (; toAdd[i] != '\0'; i++) {
    base[*cursor + i] = toAdd[i];
  }
  base[*cursor + i + 1] = '\0';
  *cursor += i;
}

Pair *generatePairEnum(int order) {
  int amount = ((order - 1) * order) / 2;
  Pair *pairs = (Pair *) malloc(sizeof(Pair) * (amount));
  unsigned int k = 0;

  for (unsigned int i = 0; i < order; i++) {
    for (unsigned int j = i + 1; j < order; j++) {
      pairs[k].e1 = i;
      pairs[k].e2 = j;
      k++;
    }
  }
  return pairs;
}
