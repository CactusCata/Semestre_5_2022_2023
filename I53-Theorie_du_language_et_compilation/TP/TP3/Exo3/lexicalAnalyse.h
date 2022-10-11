#ifndef LEXIAL_ANALYSE_H
#define LEXIAL_ANALYSE_H

#include <stdlib.h>
#include <regex.h>
#include "queue.h"
#include "utils.h"

#define MAX_LINE_FILE 1024

unilex_t *creer_unilex_table(char *fileName, unsigned int *size);

void scanRE(char *line, char **expression, char **name);

Queue *getLexicalsUnits(char *fileName, unilex_t *unilexArray, unsigned int size);

void printLexicalsUnitsCatchs(lexicalUnitCatch *lexicalUnitsCatchs, unsigned int size);

#endif