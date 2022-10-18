#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <stdio.h>

typedef struct Pair {
  int e1;
  int e2;
} Pair;

void appendText(char *base, size_t *cursor, char *toAdd);
// Add test 'toAdd' to 'base' with the index
// start to write is cursor
// /!\ cusor auto update

char *intToStr(int value);
// Convert int to char *

int readNextUInt(char *text, size_t *start);
// Return the uint at the index start of 'text'
// Return -1 if there is not int to read at 'start' index

Pair *generatePairEnum(int max);

#endif
