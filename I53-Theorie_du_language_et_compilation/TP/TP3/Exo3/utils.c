#include "utils.h"

char *getStringPart(char *sentence, unsigned int start, unsigned int end) {
  char *part = (char *) malloc(sizeof(char) * (end - start + 1));
  for (unsigned int i = 0; start < end; start++, i++) {
    part[i] = sentence[start];
  }
  part[end] = '\0';
  return part;
}

unsigned int getFileLineAmount(FILE *file) {
  unsigned int lineCount = 0;

  char lineBuffer[1024];

  while (fgets(lineBuffer, 1024, file)) {
    lineCount++;
  }

  rewind(file);
  return lineCount;
}