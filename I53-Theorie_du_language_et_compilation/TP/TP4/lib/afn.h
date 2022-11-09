#ifndef AFN_H
#define AFN_H

#include "vect.h"
#include "vectArray.h"
#include "arrayUtils.h"
#include "utils.h"
#include "stack.h"
#include "afd.h"

#define ASCII_FIRST 38
#define ASCII_LAST 127
#define MAX_SYMBOLES 90

struct AFN{
  int Q, lenSigma;
  Vect *I, *F;
  char * Sigma;
  int dico[MAX_SYMBOLES];
  VectArray **delta;
};

typedef struct AFN * AFN;

AFN afn_init(int Q, Vect *initiaux, Vect *finaux, char *Sigma);

void afn_print(AFN A);

void afn_free(AFN A);

void afn_ajouter_transition(AFN A, int q1, char s, int q2);

AFN afn_finit(char *file);

Vect *afn_epsilon_fermeture(AFN A, Vect *R);

AFD afn_determiniser(AFN A);

int afn_simuler(AFN A, char *s);

char *AFNSigmaToAFDSigma(AFN A);

void afn_toPng(AFN A, char *fileName);

void afn_spill_transitions(AFN from, AFN to, int shift);

void afn_char(AFN *C, char c);

void afn_union(AFN *C, AFN A, AFN B);

void afn_concat(AFN *C, AFN A, AFN B);

void afn_kleene(AFN *C, AFN A);

#endif
