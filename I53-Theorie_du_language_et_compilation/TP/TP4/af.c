/*
  I53 Compilation et théorie des langages
  Nicolas Méloni
  04 - 10 -2022
 */
#include <stdio.h>
#include "afd.h"

int main(int argc, char *argv[])
{
  afd A;
  char alphabet[] = "ab";
  uint finals[2] = {1,4};

  afd_init(&A, 5, alphabet, 2, 1, finals);

  afd_add_trans(&A, 1, 'a', 2);
  afd_add_trans(&A, 1, 'b', 1);
  afd_add_trans(&A, 2, 'a', 3);
  afd_add_trans(&A, 2, 'b', 1);
  afd_add_trans(&A, 3, 'a', 4);
  afd_add_trans(&A, 3, 'b', 1);
  afd_add_trans(&A, 4, 'a', 4);
  afd_add_trans(&A, 4, 'b', 4);
  //afd_print(A);
  afd_free(&A);

  //printf("============\n");

  afd B;
  afd_finit(&B, "exemple.afd");
  //afd_print(B);
  printf("%d\n", afd_simul(argv[1],B));
  afd_free(&B);

  return 0;
}
