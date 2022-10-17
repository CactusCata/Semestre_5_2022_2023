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
  return text;
}

void appendText(char *base, size_t *cursor, char *toAdd) {
  size_t i = 0;
  for (; toAdd[i] != '\0'; i++) {
    base[*cursor + i] = toAdd[i];
  }
  printf("[%s] cursor = %d + %d\n", toAdd, *cursor, i);
  base[*cursor + i + 1] = '\0';
  *cursor += i;
}
