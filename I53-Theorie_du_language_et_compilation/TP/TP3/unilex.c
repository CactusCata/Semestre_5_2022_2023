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
  char *textFileName = argv[2];

  unsigned int arraySize = 0;
  unilex_t *unilexArray = creer_unilex_table(regFileName, &arraySize);

  unsigned int size = 0;
  lexicalUnitCatch *lexicalsUnits = getLexicalsUnits(textFileName, unilexArray, &size);


  return 0;


}

Queue *getLexicalsUnits(char *fileName, unilex_t *unilexArray, unsigned int *size) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("Le fichier '%s' n'a pas été trouvé.\n", fileName);
    exit(0);
  }

  char *lineBuffer = (char *) malloc(sizeof(char) * MAX_LINE_FILE);
  fgets(lineBuffer, MAX_LINE_FILE, file);

  while (lineBuffer[0] != '\0') {
    for (unsigned int i = 0; i < size; i++) {
      unilex_t currentUnilex = unilexArray[i];
      regmatch_t pmatch;
      if (regexec(&currentUnilex.re, lineBuffer, 1, &pmatch, 0) == 0) {
        if (pmatch->rm_so == 0) {
          
        }
      }

    }
  }

  unilex_t currentUnilex = unilexArray[2];
  printf("%s\n", currentUnilex.name);
  regmatch_t *pmatch = (regmatch_t *) malloc(sizeof(regmatch_t) * 10);
  for (unsigned int i = 0; i < 10; i++) {
    if (regexec(&currentUnilex.re, lineBuffer, 10, pmatch, 0)) {
      break;
    }

    printf("Motif trouve !\n");
    printf("Début du match: %d\n", pmatch->rm_so);
    printf("Fin du match: %d\n", pmatch->rm_eo);
    lineBuffer += pmatch->rm_eo;
  }

  fclose(file);

  return NULL;

}

void printLexicalsUnitsCatchs(lexicalUnitCatch *lexicalUnitsCatchs, unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    printf("<%s,%s> ", lexicalUnitsCatchs[i].reCategory, lexicalUnitsCatchs[i].caught);
  }
}

unilex_t *creer_unilex_table(char *fileName, unsigned int *size) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("Le fichier %s n'a pas été trouvé.\n", fileName);
    exit(1);
  }

  unsigned int lineAmount = getFileLineAmount(file);
  unilex_t *unilexArray = (unilex_t *) malloc(sizeof(unilex_t) * lineAmount);

  unsigned int lineNumber = 0;
  char lineBuffer[MAX_LINE_FILE];
  while (fgets(lineBuffer, MAX_LINE_FILE, file) != NULL) {

    char *reExpr = (char *) malloc(sizeof(MAX_LINE_FILE));
    char *reName = (char *) malloc(sizeof(MAX_LINE_FILE));
    sscanf(lineBuffer, "\"%[^\"]\" %[^\n]\n", reExpr, reName);
    printf("boucle: %s %s\n", reExpr, reName);

    regex_t *rePtr = (regex_t *) malloc(sizeof(rePtr));
    if (regcomp(rePtr, reExpr, REG_EXTENDED) != 0) {
      return NULL;
    }
    unilex_t *unilexPtr = (unilex_t *) malloc(sizeof(unilex_t));
    (*unilexPtr).re = *rePtr;
    (*unilexPtr).name = reName;
    unilexArray[lineNumber++] = *unilexPtr;
  }

  *size = lineAmount;
  fclose(file);

  return unilexArray;

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
