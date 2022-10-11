// https://gist.github.com/ianmackinnon/3294587

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_FILE 1024
#define MAX_RE_INTERCEPT 32

char *buildFromNTime(char c, int n) {
  char *text = (char *) malloc(sizeof(char) * n);
  for (int i = 0; i < n; i++) {
    text[i] = c;
  }
  return text;
}

void appendString(char *base, int startWritting, char *toAdd, int endAdd) {
  for (int i = 0; i < endAdd; i++) {
    base[i + startWritting] = toAdd[i];
  }
}

int main(int argc, char *argv[]) {

  FILE *file = fopen(argv[2], "r");

  if (file == NULL) {
    printf("Le fichier '%s' n'a pas été trouvé !\n", argv[2]);
    return 1;
  }

  regmatch_t *pmatch = (regmatch_t *) malloc(sizeof(regmatch_t) * MAX_RE_INTERCEPT);
  char *buffer = (char *) malloc(sizeof(char) * MAX_LINE_FILE);

  while (!feof(file)) {
    fgets(buffer, MAX_LINE_FILE, file);
    regex_t re;

    int writted = 0;

    if (regcomp(&re, argv[1], REG_EXTENDED) != 0) {
      return 1;
    }

    char *bufferPrint = (char *) malloc(sizeof(char) * strlen(buffer));
    char *underlinePrint = (char *) malloc(sizeof(char) * strlen(buffer));


    int shift = 0;
    for (unsigned int m = 0; m < MAX_RE_INTERCEPT; m++) {

      if (regexec(&re, buffer, MAX_RE_INTERCEPT, pmatch, 0))
        break;

      if (!writted) {
        writted = 1;
      }

      appendString(bufferPrint, shift, buffer, pmatch->rm_eo);

      char *spaces = buildFromNTime(' ', pmatch->rm_so);
      char *underline = buildFromNTime('^', pmatch->rm_eo - pmatch->rm_so);
      appendString(underlinePrint, shift, spaces, pmatch->rm_so);
      appendString(underlinePrint, shift + pmatch->rm_so, underline, pmatch->rm_eo - pmatch->rm_so);
      free(spaces);
      free(underline);

      unsigned int offset = pmatch[0].rm_eo;

      //for (unsigned int g = 0; g < MAX_RE_INTERCEPT && pmatch[g].rm_so != -1; g++) {
        //printf("Match %u, Group %u: [%u-%u]: %s\n", m, g, pmatch[g].rm_so, pmatch[g].rm_eo, buffer + pmatch[g].rm_so);
      //}
      buffer += offset;
      shift += offset;
    }
    if (writted) {
      printf("%s\n", bufferPrint);
      printf("%s\n", underlinePrint);
    }
    free(bufferPrint);
    free(underlinePrint);
    regfree(&re);

  }
  return 0;
}
