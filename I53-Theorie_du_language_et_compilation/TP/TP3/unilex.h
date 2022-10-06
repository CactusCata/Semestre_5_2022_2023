#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_FILE 1024

typedef struct {
  regex_t re;
  char *name;
} unilex_t;

typedef struct {
  char *reCategory;
  char *caught;
} lexicalUnitCatch;

int main(int argc, char *argv[]);

unilex_t *creer_unilex_table(char *fileName, int *size);

void scanRE(char *line, char **expression, char **name);

unsigned int getFileLineAmount(FILE *file);

lexicalUnitCatch *getLexicalsUnits(char *fileName, unilex_t *unilexArray, unsigned int *size);

void printLexicalsUnitsCatchs(lexicalUnitCatch *lexicalUnitsCatchs, unsigned int size);
