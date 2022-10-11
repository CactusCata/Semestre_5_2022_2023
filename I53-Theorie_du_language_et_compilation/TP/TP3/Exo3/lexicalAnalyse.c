#include "lexicalAnalyse.h"

Queue *getLexicalsUnits(char *fileName, unilex_t *unilexArray, unsigned int size) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("Le fichier '%s' n'a pas été trouvé.\n", fileName);
    exit(0);
  }

  Queue *queue = createQueue();

  char *lineBuffer = (char *) malloc(sizeof(char) * MAX_LINE_FILE);
  fgets(lineBuffer, MAX_LINE_FILE, file);

  while (lineBuffer[0] != '\n') {
    for (unsigned int i = 0; i < size; i++) {
      unilex_t currentUnilex = unilexArray[i];
      regmatch_t pmatch;
      if (regexec(&currentUnilex.re, lineBuffer, 1, &pmatch, 0) == 0) {
        if (pmatch.rm_so == 0) {
          char *matchedText = getStringPart(lineBuffer, 0, pmatch.rm_eo);
          lexicalUnitCatch *lucPtr = (lexicalUnitCatch *) malloc(sizeof(lexicalUnitCatch));
          lucPtr->reCategory = currentUnilex.name;
          lucPtr->caught = matchedText;

          printf("%s %s %d\n", lucPtr->reCategory, matchedText, pmatch.rm_eo);
          add(queue, lucPtr);
          lineBuffer += pmatch.rm_eo;
          break;
        }
      }
    }
  }

  fclose(file);

  return queue;

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