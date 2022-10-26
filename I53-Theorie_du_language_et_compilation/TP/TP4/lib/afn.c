#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "afn.h"

/*
 * FUNCTION: afn_init
 * ------------------
 * initialise et retourne un AFN dont les états sont numérotés de 0 à `Q`
 * ajoute le symbole '&' en début d'alphabet si celui-ci n'y est pas déjà
 *
 * param:
 *        Q  - plus grand état de l'automate
 *        nbInitaux - nombre d'états initiaux
 *        listInitiaux - tableau de `nbInitiaux` entiers représentant les états initiaux
 *        nbFinals - nombre d'états finals
 *        listFinals - tableau de `nbFinals` entiers représentant les états finals
 *        Sigma - alphabet de l'automate
 *
 * return:
 *        un AFN dont la tableau de transition est allouée mais vide
 */
AFN  afn_init(int Q, int nbInitiaux, int * listInitiaux, int nbFinals, int * listFinals, char *Sigma){
  AFN A;
  if ( (A=malloc(sizeof(struct AFN))) == NULL){
    printf("malloc error A");
    exit(1);
  }
  A->Q = Q;

  A->lenI = nbInitiaux;
  if ( (A->I = malloc(sizeof(int)*nbInitiaux)) == NULL){
    printf("malloc error A->I");
    exit(1);
  }
  for (int i=0; i<nbInitiaux; i++) A->I[i] = listInitiaux[i];

  A->lenF = nbFinals;
  if ( (A->F = malloc(sizeof(int)*nbFinals)) == NULL){
    printf("malloc error A->F");
    exit(1);
  }
  for (int i=0; i<nbFinals; i++) A->F[i] = listFinals[i];


  A->lenSigma = strlen(Sigma);
  if (Sigma[0] != '&') A->lenSigma++;
  if ( (A->Sigma = malloc(sizeof(char)*(A->lenSigma+1)))==NULL){
    printf("malloc error A->Sigma");
    exit(1);
  }
  if (Sigma[0] != '&'){
    strcpy(A->Sigma+1,Sigma);
    A->Sigma[0]='&';
  } else {
    strcpy(A->Sigma,Sigma);
  }
  for (int i=0; i<MAX_SYMBOLES; i++) A->dico[i]=-1;
  for (int i=0; i<A->lenSigma; i++) A->dico[A->Sigma[i]-ASCII_FIRST]=i;

  if ((A->delta = malloc( sizeof(int***)*(Q+1)))==NULL){
    printf("malloc error A->Sigma");
    exit(1);
  }
  for (int q=0; q<A->Q+1; q++){
    if( (A->delta[q] = malloc( sizeof(int **)*A->lenSigma))==NULL){
      printf("malloc error A->Sigma[%d]", q);
      exit(1);
    }
    for (int s=0; s<A->lenSigma; s++)	A->delta[q][s]=NULL;
  }
  return A;
}

/*
 * FUNCTION: afn_print
 * -------------------
 * affiche l'AFN `A`
 *
 * param:
 *        A  - un AFN
 */
void afn_print(AFN A){
  printf("Q = {0,..,%d}\n", A->Q);
  printf("I = {");
  for (int i=0; i<A->lenI; i++) printf("%d,",A->I[i]);
  printf("\b}\n");

  printf("F = {");
  for (int i=0; i<A->lenF; i++) printf("%d,",A->F[i]);
  printf("\b}\n");

  int state_size = (int)(ceil(log10( (double)A->Q)));
  int padding = (state_size>=5)? (state_size-5)/2+1: 1;
  int first_column_size = state_size>=5 ? state_size+2 : 7;
  int max_cell_size = 0;

  for (int q=0; q<A->Q; q++){
    for (int s=0; s<A->lenSigma; s++){
      if (A->delta[q][s]!=NULL){
	int cell_size = 0;

	while (A->delta[q][s][cell_size]!=-1) cell_size++;
	max_cell_size = (max_cell_size < cell_size ? cell_size : max_cell_size);
      }
    }
  }
  int total_cell_size = max_cell_size*(state_size+1)+1;

  int line_length = first_column_size+1+(total_cell_size+1)*A->lenSigma;
  char * line = malloc(sizeof(char)*(line_length+2));
  for (int i=0; i<=line_length; i++) line[i]='-';
  line[line_length+1]='\0';
  printf("%s\n",line);
  printf("|%*sdelta |", padding, "");
  for (int i=0; i<A->lenSigma; i++) printf("%*c |", total_cell_size-1, A->Sigma[i]);
  printf("\n");
  printf("%s\n",line);

  char *buffer = malloc(sizeof(char)*(total_cell_size+1));
  for (int q=0; q<A->Q+1; q++){
    printf("|%*d |", padding+5, q);
    for (int i=0; i<A->lenSigma; i++){
      int s = A->dico[A->Sigma[i]-ASCII_FIRST];
      if (A->delta[q][s] != NULL){
	int j=0;
	buffer[0]='{';
	buffer[1]='\0';
	while (A->delta[q][s][j]!=-1) {
	  sprintf(buffer,"%s%d,",buffer, A->delta[q][s][j++]);
	}
	printf("%*s\b}|", total_cell_size ,buffer );
      } else {
	printf("%*s|",total_cell_size,"");
      }
    }
    printf("\n");
    printf("%s\n",line);
  }
  free(buffer);
  free(line);
}

/*
 * FUNCTION: afn_free
 * -------------------
 * libère la mémoire de l'AFN `A` initialisé par la fonction afn_init
 *
 * param:
 *        A  - un AFN
 */
void afn_free(AFN A){
  free(A->I);
  free(A->F);
  free(A->Sigma);
  for (int q=0; q<A->Q+1; q++){
    for (int s=0; s<A->lenSigma; s++){
      if (A->delta[q][s]!=NULL)
	      free(A->delta[q][s]);
    }
    free(A->delta[q]);
  }
  free(A->delta);
  free(A);
}


/*
 * FUNCTION: afn_ajouter_transition
 * --------------------------------
 * ajoute la transition  `q1` -- `s` --> `q2` à l'automate `A` où l'ensemble des transitions
 * partant de l'état `q1` et étiquetées par le symbole `s` delta[q][s] est un tableau
 * d'entiers trié dans l'ordre croissant et se terminant par -1, NULL si vide
 *
 * param:
 *        A  - un AFN
 *        q1 - état de départ de la transition
 *        s  - étiquette de la transition
 *        q2 - état d'arrivée de la transition
 */
void afn_ajouter_transition(AFN A, int q1, char s, int q2) {
  unsigned int arraySize = A->Q + 3; // max - min + 1 + epsilonTransition + le -1 à la fin;
  int sommet = A->dico[s-ASCII_FIRST];

  if (A->delta[q1][sommet] == NULL) {
    A->delta[q1][sommet] = (int *) malloc(sizeof(int) * arraySize);
    fillIntArray(A->delta[q1][sommet], arraySize, -1);
    A->delta[q1][sommet][0] = q2;
  } else {
      size_t q2InsertionIndex = 0;
      while (A->delta[q1][sommet][q2InsertionIndex] < q2 && A->delta[q1][sommet][q2InsertionIndex] != -1) {
          q2InsertionIndex++;
      }
      shiftValuesArrayToRight(A->delta[q1][sommet], arraySize, q2InsertionIndex);
      A->delta[q1][sommet][q2InsertionIndex] = q2;
  }
}

/*
 * FUNCTION: afn_finit
 * ------------------
 * initialise et renvoie un AFN à partir du fichier `file` écrit au format:
 *
 *  'nombre_etat
 *  'nombre_etats_initiaux
 *  'etat_initial_1 etat_initial_2 ... etat_initial_n
 *  'nombre_etats_finals
 *  'etat_final_1 etat_final_2 ... etat_final_n
 *  'alphabet
 *  'etat_i1 symbole_k1 etat_j1
 *  'etat_i2 symbole_k2 etat_j2
 *  '...
 *  'etat_in symbole_kn etat_jn
 *
 * param :
 *         file - un nom de fichier
 * return:
 *         un AFN complet
 */
AFN afn_finit(char *fileName) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("The file '%s' do not exist.\n", fileName);
    exit(1);
  }

  uint nbEtat;
  uint nbEtatInitiaux;

  fscanf(file, "%d\n", &nbEtat);
  fscanf(file, "%d\n", &nbEtatInitiaux);

  char *lineBuffer = (char *) malloc(sizeof(char) * 1024);
  fgets(lineBuffer, 1024, file);
  int *listInitiaux = getAllIntInLine(lineBuffer, nbEtatInitiaux);

  uint nbEtatFinaux;
  fscanf(file, "%d\n", &nbEtatFinaux);

  fgets(lineBuffer, 1024, file);
  int *listFinals = getAllIntInLine(lineBuffer, nbEtatFinaux);
  free(lineBuffer);

  char *Sigma;
  fscanf(file, "%ms\n", &Sigma);

  AFN B = afn_init(nbEtat, nbEtatInitiaux, listInitiaux, nbEtatFinaux, listFinals, Sigma);

  int etat_i, etat_j;
  char symbol;
  while (!feof(file)) {
    if (fscanf(file, "%d %c %d\n", &etat_i, &symbol, &etat_j) == 3) {
      afn_ajouter_transition(B, etat_i, symbol, etat_j);
    }
  }

  fclose(file);
  free(Sigma);
  free(listInitiaux);
  free(listFinals);

  return B;
}

/*
 * FUNCTION: afn_epsilon_fermeture
 * -------------------------------
 * renvoie un pointeur vers l'epsilon fermeture de l'ensemble d'états `R`
 *
 * param:
 *        A - un AFN
 *        R - un ensemble d'états sous forme de tableau d'entiers triés par ordre croissant
 * terminant par -1, NULL si vide
 */

int * afn_epsilon_fermeture(AFN A, int *R, int RSize) {

  // majoration du nombre de valeurs atteintes par le nombre d'état possible
  int stateAmount = A->Q + 2;
  int *fermeture = (int *) malloc(sizeof(int) * stateAmount);
  int cursorFermeture = 0;
  fillIntArray(fermeture, stateAmount, -1);

  if (R == NULL) {
    return fermeture;
  }

  Stack *stack = createStack();

  for (int index = 0; index < RSize && R[index] != -1; index++) {
    push(stack, R[index]);
    fermeture[cursorFermeture++] = R[index];
  }

  while (!stackIsEmpty(stack)) {
    int q = pop(stack);
    int letter = A->dico['&'-ASCII_FIRST];
    if (A->delta[q][letter] != NULL) {
      for (int deltaCursor = 0; A->delta[q][letter][deltaCursor] != -1; deltaCursor++) {
        int q_sec = A->delta[q][letter][deltaCursor];
        if (!intIsInArray(q_sec, fermeture, stateAmount)) {
          fermeture[cursorFermeture++] = q_sec;
          push(stack, q_sec);
        }
      }
    }
  }
  freeStack(stack);
  return fermeture;
}

AFD afn_determiniser(AFN A) {
  printArray(A->I, A->lenI);
  int *Q_0 = afn_epsilon_fermeture(A, A->I, A->lenI);

  int stateAmountAFN = A->Q + 2;
  // le nombre de sous partie d'un ensemble à n + 1 éléments est 2^(n + 1)
  int SMaxSize = 1 << stateAmountAFN;
  printf("Taille : %d\n", SMaxSize);
  int **S = (int **) malloc(sizeof(int *) * SMaxSize);
  fill3DArrayWithNull(S, SMaxSize);


  // Vaut l'indice d'écriture de S (vaut également à un tout instant le nombre d'élément de S)
  int sCursorW = 0;
  S[sCursorW++] = Q_0;

  // Il peut y avoir au maximum le même nombre d'état finaux que d'état dans S
  int *etatsFinaux = (int *) malloc(sizeof(int) * SMaxSize);
  fillIntArray(etatsFinaux, SMaxSize, -1);
  int etatsFinauxCursor = 0;


  int maxTransitionSize = A->lenSigma * SMaxSize;
  int *stateQ0 = (int *) malloc(sizeof(int) * maxTransitionSize);
  char *stateSymb = (char *) malloc(sizeof(char) * maxTransitionSize);
  int *stateQ1 = (int *) malloc(sizeof(int) * maxTransitionSize);
  fillIntArray(stateQ0, maxTransitionSize, -1);
  fillCharArray(stateSymb, maxTransitionSize, '?');
  fillIntArray(stateQ1, maxTransitionSize, -1);
  printf("Size of arrays is = %d\n", maxTransitionSize);
  int transitionCursor = 0;

  for (int sCursorR = 0; sCursorR < SMaxSize && S[sCursorR] != NULL; sCursorR++) {
    printf("                                       \n");
    printf("                                       \n");
    printf("                                       \n");
    printf("S[%d] is running...\n", sCursorR);
    int *setOfState = S[sCursorR];
    printArrayStopValue(setOfState, -1);

    for (int indexAlphabet = 1; indexAlphabet < A->lenSigma; indexAlphabet++) {
        char letter = A->Sigma[indexAlphabet];
        int letterInt = A->dico[letter-ASCII_FIRST];
        printf("\t\tUse letter %c\n", letter);

        int *stateReached = (int *) malloc(sizeof(int) * stateAmountAFN);
        fillIntArray(stateReached, stateAmountAFN, -1);
        bool addedInS = False;

        for (int stateCusor = 0; (stateCusor < stateAmountAFN) && setOfState[stateCusor] != -1; stateCusor++) {
          printf("\tproccessing stateCusor = %d\n", stateCusor);
          int q = setOfState[stateCusor];

          printf("\t\t\tAdding epsilon fermeture...\n");
          int *tmp = afn_epsilon_fermeture(A, A->delta[q][letterInt], stateAmountAFN);
          printf("\t\t\tEpsilon fermeture added !\n");
          printf("Valeur de l'espsilon fermeture: \n");
          printArrayStopValue(tmp, -1);

          concatenateArrays(stateReached, tmp, stateAmountAFN);
          printf("The state of reached is: \n");
          printArrayStopValue(stateReached, -1);
          free(tmp);
        }

        int index = -1;
        if (!TwoDArrayIsInThreeDArray(stateReached, S, SMaxSize, &index)) {
          index = sCursorW;
          printf("\t\t\tAppend new state on index %d!\n", index);
          printArrayStopValue(stateReached, -1);
          S[sCursorW++] = stateReached;
          addedInS = True;
        }

        printf("\t\t\tIndex is %d.\n", index);

        printf("\t\t\tWritting at index %d!\n", transitionCursor);
        stateQ0[transitionCursor] = sCursorR;
        stateSymb[transitionCursor] = letter;
        stateQ1[transitionCursor] = index;
        printf("\t\t\tWe added %d %c %d\n", stateQ0[transitionCursor], stateSymb[transitionCursor], stateQ1[transitionCursor]);
        transitionCursor++;

        // Ajout des états finaux
        for (int cursor = 0; stateReached[cursor] != -1; cursor++) {
          int state = stateReached[cursor];
          if (intIsInArray(state, A->F, A->lenF)) {
            if (!intIsInArray(index, etatsFinaux, etatsFinauxCursor)) {
              etatsFinaux[etatsFinauxCursor++] = index;
              break;
            }
          }
        }

        if (!addedInS) {
          free(stateReached);
        }
    }
  }

  etatsFinaux = ajustArray(etatsFinaux, etatsFinauxCursor);

  char newSigma[A->lenSigma];
  for (int i = 0; i < A->lenSigma - 1; i++) {
    newSigma[i] = A->Sigma[i + 1];
  }
  newSigma[A->lenSigma - 1] = '\0';

  AFD B = afd_init(sCursorW - 1, 0, etatsFinauxCursor, etatsFinaux, newSigma);

  for (int i = 0; i < transitionCursor; i++) {
    afd_ajouter_transition(B, stateQ0[i], stateSymb[i], stateQ1[i]);
  }

  free(stateQ0);
  free(stateSymb);
  free(stateQ1);
  free(etatsFinaux);

  for (int i = 0; i < SMaxSize && S[i] != NULL; i++) {
    free(S[i]);
  }
  free(S);

  return B;
}
/*
 * FUNCTION: afn_simuler
 * ---------------------
 * renvoie 1 si la chaine `s` est acceptée par l'AFN `A`, 0 sinon
 *
 * param:
 *        A - un AFN
 *        s - la chaine de caractères à analyser
 */
int afn_simuler(AFN A, char *s);
