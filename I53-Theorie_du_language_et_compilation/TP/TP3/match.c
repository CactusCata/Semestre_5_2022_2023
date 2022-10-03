# include <regex.h>
# include <stdio.h>
# include <stdlib.h>

int main(int argc, char *argv[]) {
  regex_t re;

  if (regcomp(&re, argv[1], REG_EXTENDED) != 0) {
    return 1;
  }

  regmatch_t pmatch;
  if (regexec(&re, argv[2], 1, &pmatch, 0) == 0) {

    printf("Motif trouvé !\n");
    printf("Début du match: %d\n", pmatch.rm_so);
    printf("Fin du match: %d\n", pmatch.rm_eo);
  } else {
    printf("Motif non trouvé !\n");
  }

  regfree(&re);
  return 0;
}
