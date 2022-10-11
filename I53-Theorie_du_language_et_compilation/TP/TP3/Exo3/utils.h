#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

typedef struct {
  regex_t re;
  char *name;
} unilex_t;

typedef struct {
  char *reCategory;
  char *caught;
} lexicalUnitCatch;

unsigned int getFileLineAmount(FILE *file);

char *getStringPart(char *sentence, unsigned int start, unsigned int end);

#endif