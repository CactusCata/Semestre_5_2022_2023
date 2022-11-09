#include "afd.h"

/*
 * FUNCTION: afd_init
 * ------------------
 * initialise et retourne un AFD dont les états sont numérotés de 0 à `Q`
 *
 * param:
 *        Q  - plus grandétat de l'automate
 *        q0 - état inital
 *        nbFinals - nombre d'états finals
 *        listFinals - tableau de `nbFinals` entiers représentant les états finals
 *        Sigma - alphabet de l'automate
 *
 * return:
 *        un AFD dont la tableau de transition est allouée mais vide
 */
AFD afd_init(int Q, int q0, Vect *listFinals, char *Sigma) {
  AFD A = malloc(sizeof(struct AFD));
  throwMallocErrorIfTrue(A == NULL);

  A->Q = Q;
  A->q0 = q0;
  A->F = vectCopy(listFinals);

  // Alphabet
  A->lenSigma = strlen(Sigma);
  A->Sigma = malloc(sizeof(char) * (A->lenSigma + 1));
  throwMallocErrorIfTrue(A->Sigma == NULL);
  strcpy(A->Sigma,Sigma);
  for (int i=0; i<MAX_SYMBOLES; i++) A->dico[i]=-1;
  for (int i=0; i<A->lenSigma; i++) A->dico[Sigma[i]-ASCII_FIRST]=i;

  // Delta
  A->delta = createVectArray();
  for (int q = 0; q < A->Q + 1; q++) {
    Vect *vect = createVect(false);
    expendVectSize(vect, A->lenSigma);
    vect->size = A->lenSigma;
    vectArrayAdd(A->delta, vect);
  }

  return A;
}

/*
 * FUNCTION: afd_ajouter_transition
 * --------------------------------
 * ajoute la transition  `q1` -- `s` --> `q2` à l'automate `A`
 *
 * param:
 *        A  - un AFD
 *        q1 - état de départ de la transition
 *        s  - étiquette de la transition
 *        q2 - état d'arrivée de la transition
 */
void afd_ajouter_transition(AFD A, int q1, char s, int q2) {
  if (q1 < 0 || q1 > A->Q) {
    printf("Trying to execute function \"afd_ajouter_transition(AFD A, q1: %d, s: %c, q2: %d)\"...\n", q1, s, q2);
    printf("q1 need to be in range of [%d, %d]\n", 0, A->Q);
    exit(1);
  }
  
  if (q2 < 0 || q2 > A->Q) {
    printf("Trying to execute function \"afd_ajouter_transition(AFD A, q1: %d, s: %c, q2: %d)\"...\n", q1, s, q2);
    printf("q2 need to be in range of [%d, %d]\n", 0, A->Q);
    exit(1);
  }

  if (!charArrayContrains(A->Sigma, A->lenSigma, s)) {
    printf("Trying to execute function \"afd_ajouter_transition(AFD A, q1: %d, s: %c, q2: %d)\"...\n", q1, s, q2);
    printf("s need to be in range array:");
    printArrayChar(A->Sigma, A->lenSigma);
    printf("\n");
    exit(1);
  }
  
  int res = A->dico[s-ASCII_FIRST];
  vectSet(vectArrayGet(A->delta, q1), q2, res);
}


/*
 * FUNCTION: afd_print
 * -------------------
 * affiche l'AFD `A`
 *
 * param:
 *        A  - un AFD
 */
void afd_print(AFD A){
  printf("Q = {0,..,%d}\n", A->Q);
  printf("q0 = %d\n", A->q0);
  printf("F = ");
  printVect(A->F);

  // Alloc textMatrix
  char ***textMatrix = (char ***) malloc(sizeof(char **) * (A->Q + 2));
  int **dimsMatrix = (int **) malloc(sizeof(int *) * (A->Q + 2));

  throwMallocErrorIfTrue(textMatrix == NULL);
  throwMallocErrorIfTrue(dimsMatrix == NULL);

  // Init first line (delta + letters of alphabet)
  textMatrix[0] = (char **) malloc(sizeof(char *) * (A->lenSigma + 1));
  dimsMatrix[0] = (int *) malloc(sizeof(int) * (A->lenSigma + 1));

  throwMallocErrorIfTrue(textMatrix[0] == NULL);
  throwMallocErrorIfTrue(dimsMatrix[0] == NULL);

  char *cached = (char *) malloc(sizeof(char) * 32);
  throwMallocErrorIfTrue(cached == NULL);
  int z = 0;
  appendText(cached, "delta", &z);
  textMatrix[0][0] = cached;
  dimsMatrix[0][0] = strlen(textMatrix[0][0]);
  for (int alphaIndex = 1; alphaIndex < A->lenSigma + 1; alphaIndex++) {
    textMatrix[0][alphaIndex] = (char *) malloc(sizeof(char) * 2);
    throwMallocErrorIfTrue(textMatrix[0][alphaIndex] == NULL);
    textMatrix[0][alphaIndex][0] = A->Sigma[alphaIndex - 1];
    textMatrix[0][alphaIndex][1] = '\0';
    dimsMatrix[0][alphaIndex] = 1;
  }

  // Fill others lines
  for (int stateIndex = 1; stateIndex < A->Q + 2; stateIndex++) {
    dimsMatrix[stateIndex] = (int *) malloc(sizeof(int) * (A->lenSigma + 1));
    textMatrix[stateIndex] = (char **) malloc(sizeof(char *) * (A->lenSigma + 1));
    throwMallocErrorIfTrue(dimsMatrix[stateIndex] == NULL);
    throwMallocErrorIfTrue(textMatrix[stateIndex] == NULL);

    char *stateIndexText = (char *) malloc(sizeof(char) * 15);
    throwMallocErrorIfTrue(stateIndexText == NULL);
    sprintf(stateIndexText, "%d", stateIndex - 1);
    textMatrix[stateIndex][0] = stateIndexText;
    dimsMatrix[stateIndex][0] = strlen(stateIndexText);

    Vect *vect = vectArrayGet(A->delta, stateIndex - 1);
    for (int alphabetIndex = 1; alphabetIndex < A->lenSigma + 1; alphabetIndex++) {
      if (alphabetIndex - 1 >= vect->size || vectGet(vect, alphabetIndex - 1) == -1) {
        char *q2Null = (char *) malloc(sizeof(char) * 2);
        throwMallocErrorIfTrue(q2Null == NULL);
        q2Null[0] = ' ';
        q2Null[1] = '\0';
        textMatrix[stateIndex][alphabetIndex] = q2Null;
        dimsMatrix[stateIndex][alphabetIndex] = 1;
      } else {
        int q2 = vectGet(vect, alphabetIndex - 1);
        char *q2Str = (char *) malloc(sizeof(char) * 15);
        throwMallocErrorIfTrue(q2Str == NULL);
        sprintf(q2Str, "%d", q2);
        textMatrix[stateIndex][alphabetIndex] = q2Str;
        dimsMatrix[stateIndex][alphabetIndex] = strlen(q2Str);
      }
    }
  }

  printMatrix(textMatrix, dimsMatrix, A->Q + 2, A->lenSigma + 1);

  for (int line = 0; line < A->Q + 2; line++) {
    for (int col = 0; col < A->lenSigma + 1; col++) {
      free(textMatrix[line][col]);
    }
    free(textMatrix[line]);
    free(dimsMatrix[line]);
  }
  free(textMatrix);
  free(dimsMatrix);
}

/*
 * FUNCTION: afd_free
 * -------------------
 * libère la mémoire de l'AFD `A` initialisé par la fonction afd_init
 *
 * param:
 *        A  - un AFD
 */
void afd_free(AFD A){
  freeVect(A->F);
  free(A->Sigma);
  for (int q = 0; q < A->Q + 1; q++) {
    freeVect(vectArrayGet(A->delta, q));
  }
  freeVectArray(A->delta);
  free(A);
}


/*
 * FUNCTION: afd_finit
 * ------------------
 * initialise et renvoie un AFD à partir du fichier `file` écrit au format:
 *
 *  'nombre_etat
 *  'etat_initial
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
 *         un AFD complet
 */
AFD afd_finit(char *fileName) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("The file '%s' do not exist.\n", fileName);
    exit(1);
  }

  int Q;
  int q0;
  int nbFinals;
  fscanf(file, "%d\n", &Q);
  fscanf(file, "%d\n", &q0);
  fscanf(file, "%d\n", &nbFinals);

  char *lineBuffer = (char *) malloc(sizeof(char) * 1024);
  throwMallocErrorIfTrue(lineBuffer == NULL);
  fgets(lineBuffer, 1024, file);
  int *listFinals = getAllIntInLine(lineBuffer, nbFinals);
  Vect *vectFinaux = createVectFromIntArray(listFinals, nbFinals, false);
  free(lineBuffer);

  char *Sigma;
  fscanf(file, "%ms\n", &Sigma);

  AFD A = afd_init(Q, q0, vectFinaux, Sigma);

  free(listFinals);
  freeVect(vectFinaux);

  int etat_i, etat_j;
  char symbol;
  while (!feof(file)) {
    if (fscanf(file, "%d %c %d\n", &etat_i, &symbol, &etat_j) == 3) {
      afd_ajouter_transition(A, etat_i, symbol, etat_j);
    }
  }

  fclose(file);
  free(Sigma);

  return A;
}

/*
 * FUNCTION: afd_simuler
 * ---------------------
 * renvoie 1 si la chaine `s` est acceptée par l'AFD `A`, 0 sinon
 *
 * param:
 *        A - un AFD
 *        s - la chaine de caractères à analyser
 */
int afd_simuler(AFD A, char *s) {
  unsigned int cursor = 0;
  int q = A->q0;

  while ((s[cursor] != '\0') && (s[cursor] != '\n')) {
    if (!charArrayContrains(A->Sigma, A->lenSigma, s[cursor])) {
      return 0;
    }
    int letterInt = A->dico[s[cursor]-ASCII_FIRST];
    q = vectGet(vectArrayGet(A->delta, q), letterInt);
    cursor++;
  }

  return vectContrainsValue(A->F, q);

}

/**
 * @brief Crée une image à partir d'un AFD.
 * L'image créée sera placée dans le dossier ./data/graphViz/png/fileName.png
 * L'image est créée à l'aide du module graphViz
 * 
 * @param A un AFD
 * @param fileName le nom donné au fichier crée
 */
void afd_toPng(AFD A, char *fileName) {
  char dotExtension[] = "dot";
  char dotPath[] = "../data/graphViz/dot/";
  char pngExtension[] = "png";
  char pngPath[] = "../data/graphViz/png/";

  char destinationDotFile[128];
  char destinationPngFile[128];

  sprintf(destinationDotFile, "%s%s.%s", dotPath, fileName, dotExtension);
  sprintf(destinationPngFile, "%s%s.%s", pngPath, fileName, pngExtension);

  FILE *file = fopen(destinationDotFile, "w");

  graphVizInitGraph(file);

  // Add initial state
  graphVizAddInitialState(file, A->q0);

  // Add final state
  for (int i = 0; i < A->F->size; i++) {
    graphVizAddFinalState(file, vectGet(A->F, i));
  }

  // Add transitions
  for (int q = 0; q < A->Q + 1; q++) {
    Vect *vect = vectArrayGet(A->delta, q);
    for (int alphabetIndex = 0; alphabetIndex < A->lenSigma; alphabetIndex++) {
      char letter = A->Sigma[alphabetIndex];
      if (alphabetIndex < vect->size && vectGet(vect, alphabetIndex) != -1) {
        int q2 = vectGet(vect, alphabetIndex);
        graphVizAddTransition(file, q, letter, q2);
      }
    }
  }

  graphVizEnd(file);
  fclose(file);

  char cmd[512];
  sprintf(cmd, "dot -Tpng %s > %s", destinationDotFile, destinationPngFile);
  system(cmd);

}