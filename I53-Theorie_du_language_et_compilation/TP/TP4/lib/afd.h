#ifndef AFD_H
#define AFD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vect.h"
#include "vectArray.h"
#include "arrayUtils.h"
#include "utils.h"
#include "graphviz.h"

#define ASCII_FIRST 38
#define ASCII_LAST 127
#define MAX_SYMBOLES 90


struct AFD{
  int Q, q0, lenSigma;
  Vect *F;
  char *Sigma;
  int dico[MAX_SYMBOLES];
  VectArray *delta;
};

typedef struct AFD * AFD;

AFD afd_init(int Q, int q0, Vect *finaux, char *Sigma);

void afd_ajouter_transition(AFD A, int q1, char s, int q2);

void afd_print(AFD A);

void afd_free(AFD A);

AFD afd_finit(char *file);

int afd_simuler(AFD A, char *s);

void afd_toPng(AFD A, char *fileName);

#endif
