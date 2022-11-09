#include "main.h"

int main(int argc, char *argv[]){

  if (argc < 2) {
    printf("usage: %s <exreg> <chaine>\n", argv[0]);
    return 1;
  }

  char *re = argv[1];
  char *text = argv[2];

  AFN A = buildAFNFromRE(re);
  if (afn_simuler(A, text)) {
    printf("acceptée\n\n");
  } else {
    printf("rejetee\n\n");
  }
  afn_free(A);

}
