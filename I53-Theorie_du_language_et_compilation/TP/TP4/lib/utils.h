#ifndef UTILS_H
#define UTILS_H

#include "stdio.h"
#include "stdlib.h"

typedef unsigned int uint;

typedef enum bool {
  False,
  True
} bool;

int getNextIntFromLine(char *lineBuffer, unsigned int *cursor);

int *getAllIntInLine(char *line, int sizeArray);

#endif
