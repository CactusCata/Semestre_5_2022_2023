#include "unilex.h"

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Veuillez préciser le nom du fichier contenant les règles re.\n");
    return 0;
  }

  if (argc < 3) {
    printf("Veuillez préciser le nom du fichier à analyser.\n");
    return 0;
  }

  char *regFileName = argv[1];
  //char *textFileName = argv[2];

  int arraySize = 0;
  unilex_t *unilexArray = creer_unilex_table(regFileName, &arraySize);

  for (int i = 0; i < arraySize; i++) {
    unilex_t unilex = unilexArray[i];
    printf("reg: text: %s\n", unilex.name);
  }

  return 0;


}

unilex_t *creer_unilex_table(char *fileName, int *size) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("Le fichier %s n'a pas été trouvé.\n", fileName);
    exit(1);
  }

  char lineBuffer[MAX_LINE_FILE];
  unsigned int fileLineAmount = getFileLineAmount(file);
  unilex_t *unilexArray = (unilex_t *) malloc(sizeof(unilex_t) * fileLineAmount);

  for (unsigned int i = 0; i < fileLineAmount; i++) {
    char *expression = (char *) malloc(sizeof(char *));
    char *name = (char *) malloc(sizeof(char *));
    fgets(lineBuffer, MAX_LINE_FILE, file);
    scanRE(lineBuffer, &expression, &name);

    regex_t re;
    if (regcomp(&re, expression, REG_EXTENDED) != 0) {
      return NULL;
    }

    unilex_t unilex = {.re = re, .name = name};
    unilexArray[i] = unilex;
  }

  *size = fileLineAmount;
  fclose(file);

  return unilexArray;

}

void scanRE(char *line, char **expression, char **name) {
  line++;
  unsigned int exprSize = 0;
  while (*line != '"') {
    line++;
    exprSize++;
  }

  char *re = (char *) malloc(sizeof(char) * exprSize);
  *expression = re;

  for (unsigned int i = 0; i < exprSize; i++) {
    re[i] = line[i + 1];
  }

  line++;

  unsigned int nameSize = 0;
  while (*(line + 1) != '\n') {
    nameSize++;
  }

  char *reName = (char *) malloc(sizeof(char) * nameSize);
  *name = rename;

  for (unsigned int i = 0; i < nameSize; i++) {
    reName[i] = line[i];
  }

}

unsigned int getFileLineAmount(FILE *file) {
  unsigned int lineCount = 0;

  char lineBuffer[MAX_LINE_FILE];

  while (fgets(lineBuffer, MAX_LINE_FILE, file)) {
    lineCount++;
  }

  rewind(file);
  return lineCount;
}
