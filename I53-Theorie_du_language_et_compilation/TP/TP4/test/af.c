#include "af.h"

int main(int argc, char *argv[]){

  /**
  AFD afd = afd_finit("afd1.afd");
  afd_print(afd);

  char sentence1[] = "abbabbaba";
  printf("La chaine %s est acceptée ? %d\n", sentence1, afd_simuler(afd, sentence1));

  char sentence2[] = "abbabbbbbabb";
  printf("La chaine %s est acceptée ? %d\n", sentence2, afd_simuler(afd, sentence2));

  afd_free(afd);
  */

  AFN afn = afn_finit("../data/afn1.afn");
  afn_print(afn);

  afn_free(afn);

  /**
  int Q = 3;
  int q0 = 0;
  int nbFinals = 2;
  int listFinals[2] = {1, 3};
  int nbInitaux = 2;
  int listInitiaux[2] = {0, 1};
  char Sigma[]="abc";

  AFD  A;
  A = afd_init(Q, q0, nbFinals, listFinals, Sigma);

  afd_ajouter_transition(A, 0,'a',2);
  afd_ajouter_transition(A, 0,'b',1);
  afd_ajouter_transition(A, 0,'c',0);
  afd_ajouter_transition(A, 1,'a',2);
  afd_ajouter_transition(A, 1,'b',0);
  afd_ajouter_transition(A, 1,'c',3);
  afd_ajouter_transition(A, 2,'a',3);
  afd_ajouter_transition(A, 2,'b',1);
  afd_ajouter_transition(A, 2,'c',3);
  afd_ajouter_transition(A, 3,'a',2);
  afd_ajouter_transition(A, 3,'b',1);
  afd_ajouter_transition(A, 3,'c',3);

  printf("AFD: \n");
  afd_print(A);

  afd_free(A);

  AFN B;
  B = afn_init(Q,nbInitaux,listInitiaux,nbFinals,listFinals,Sigma);

  afn_ajouter_transition(B, 0,'a',2);
  afn_ajouter_transition(B, 0,'a',1);
  afn_ajouter_transition(B, 0,'a',0);
  afn_ajouter_transition(B, 1,'a',2);
  afn_ajouter_transition(B, 1,'b',0);
  afn_ajouter_transition(B, 1,'c',3);
  afn_ajouter_transition(B, 2,'a',3);
  afn_ajouter_transition(B, 2,'b',1);
  afn_ajouter_transition(B, 2,'c',3);
  afn_ajouter_transition(B, 3,'a',2);
  afn_ajouter_transition(B, 3,'b',1);
  afn_ajouter_transition(B, 3,'c',3);

  printf("AFN\n");
  afn_print(B);

  afn_free(B);
  */

  return 0;
}
