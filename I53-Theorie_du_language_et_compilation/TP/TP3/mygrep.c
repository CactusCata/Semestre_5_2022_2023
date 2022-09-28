// https://gist.github.com/ianmackinnon/3294587

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_FILE 1024
#define MAX_RE_INTERCEPT 32

void printNTime(unsigned int time, char c) {
  for (unsigned int i = 0; i < time; i++) {
    printf("%c", c);
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

    if (regcomp(&re, argv[1], REG_EXTENDED) != 0) {
      return 1;
    }

    for (unsigned int m = 0; m < MAX_RE_INTERCEPT; m++) {

      if (regexec(&re, buffer, MAX_RE_INTERCEPT, pmatch, 0))
        break;

      unsigned int offset = pmatch[0].rm_eo;

      printNTime(pmatch->rm_so, ' ');
      printNTime(pmatch->rm_eo - pmatch->rm_so, '^');

      for (unsigned int g = 0; g < MAX_RE_INTERCEPT && pmatch[g].rm_so != -1; g++) {

        printf("Match %u, Group %u: [%u-%u]: %s\n",
                 m, g, pmatch[g].rm_so, pmatch[g].rm_eo,
                 buffer + pmatch[g].rm_so);

      }
      buffer += offset;
    }
    regfree(&re);

  }
  return 0;
}
