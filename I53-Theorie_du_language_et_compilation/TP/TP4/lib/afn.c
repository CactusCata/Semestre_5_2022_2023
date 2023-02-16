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
AFN afn_init(int Q, Vect *initiaux, Vect *finaux, char *Sigma) {
  AFN A = malloc(sizeof(struct AFN));
  throwMallocErrorIfTrue(A == NULL);

  A->Q = Q;
  A->I = vectCopy(initiaux);
  A->F = vectCopy(finaux);

  // Alphabet
  A->lenSigma = strlen(Sigma);
  if (Sigma[0] != '&') A->lenSigma++;
  A->Sigma = malloc(sizeof(char) * (A->lenSigma + 1));
  throwMallocErrorIfTrue(A->Sigma == NULL);

  if (Sigma[0] != '&'){
    strcpy(A->Sigma+1,Sigma);
    A->Sigma[0]='&';
  } else {
    strcpy(A->Sigma,Sigma);
  }
  for (int i=0; i<MAX_SYMBOLES; i++) A->dico[i]=-1;
  for (int i=0; i<A->lenSigma; i++) A->dico[A->Sigma[i]-ASCII_FIRST]=i;

  // Delta
  A->delta = malloc(sizeof(VectArray **) * (Q + 1));
  throwMallocErrorIfTrue(A->delta == NULL);

  for (int q = 0; q < A->Q + 1; q++) {
    A->delta[q] = createVectArray();
    for (int s = 0; s < A->lenSigma; s++)	{
      vectArrayAdd(A->delta[q], NULL);
    }
  }
  return A;
}

/**
 * 
 * +-------+-------+-----+---------+
 * | Delta |   &   |  a  |    b    |
 * +-------+-------+-----+---------+
 * |  {0}  | {0,1} | {0} | {0,1,3} |
 * +-------+-------+-----+---------+
 * | {0,1} |  {0}  | {1} |   {0}   |
 * +-------+-------+-----+---------+
 * 
 * 
 * 
*/
/*
 * FUNCTION: afn_print
 * -------------------
 * affiche l'AFN `A`
 *
 * param:
 *        A  - un AFN
 */
void afn_print(AFN A) {
  printf("Q = {0,..,%d}\n", A->Q);
  printVect(A->I);
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
  appendText(cached, "Delta", &z);
  textMatrix[0][0] = cached;
  dimsMatrix[0][0] = 5;
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

    for (int alphabetIndex = 1; alphabetIndex < A->lenSigma + 1; alphabetIndex++) {
      Vect *vect = vectArrayGet(A->delta[stateIndex - 1], alphabetIndex - 1);
      if (vect == NULL) {
        char *vectNull = (char *) malloc(sizeof(char) * 1);
        throwMallocErrorIfTrue(vectNull == NULL);
        vectNull[0] = '\0';
        textMatrix[stateIndex][alphabetIndex] = vectNull;
        dimsMatrix[stateIndex][alphabetIndex] = 0;
      } else {
        char *vectSerialized = serializeVectArray(vect);
        textMatrix[stateIndex][alphabetIndex] = vectSerialized;
        dimsMatrix[stateIndex][alphabetIndex] = strlen(vectSerialized);
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
 * FUNCTION: afn_free
 * -------------------
 * libère la mémoire de l'AFN `A` initialisé par la fonction afn_init
 *
 * param:
 *        A  - un AFN
 */
void afn_free(AFN A){
  freeVect(A->I);
  freeVect(A->F);
  free(A->Sigma);

  for (int q = 0; q < A->Q + 1; q++) {
    VectArray *vectArray = A->delta[q]; 
    for (int s = 0; s < A->lenSigma; s++) {
      Vect *vect = vectArrayGet(vectArray, s);
      if (vect != NULL) {
        freeVect(vect);
      } 
    }
    freeVectArray(vectArray);
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
  int letterInt = A->dico[s-ASCII_FIRST];

  VectArray *vectArray = A->delta[q1];

  if (vectArrayGet(vectArray, letterInt) == NULL) {
    Vect *vect = createVect(true);
    vectAdd(vect, q2);
    vectArraySet(A->delta[q1], vect, letterInt);
  } else {
    Vect *vect = vectArrayGet(vectArray, letterInt);
    vectAdd(vect, q2);
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

  uint nbEtat; // nombre d'état
  uint nbEtatInitiaux; // nombre d'état initiaux

  fscanf(file, "%d\n", &nbEtat);
  fscanf(file, "%d\n", &nbEtatInitiaux);

  char *lineBuffer = (char *) malloc(sizeof(char) * 1024);
  throwMallocErrorIfTrue(lineBuffer == NULL);
  fgets(lineBuffer, 1024, file);
  int *listInitiaux = getAllIntInLine(lineBuffer, nbEtatInitiaux);
  Vect *vectInitiaux = createVectFromIntArray(listInitiaux, nbEtatInitiaux, false); // liste des initiaux
  free(listInitiaux);

  uint nbEtatFinaux;
  fscanf(file, "%d\n", &nbEtatFinaux); // nombre d'état finaux

  fgets(lineBuffer, 1024, file);
  int *listFinals = getAllIntInLine(lineBuffer, nbEtatFinaux);
  Vect *vectFinaux = createVectFromIntArray(listFinals, nbEtatFinaux, false); // liste des états finaux
  free(listFinals);
  free(lineBuffer);

  char *Sigma;
  fscanf(file, "%ms\n", &Sigma); // alphabet

  AFN B = afn_init(nbEtat, vectInitiaux, vectFinaux, Sigma);

  int etat_i, etat_j;
  char symbol;
  while (!feof(file)) {
    if (fscanf(file, "%d %c %d\n", &etat_i, &symbol, &etat_j) == 3) {
      afn_ajouter_transition(B, etat_i, symbol, etat_j);
    }
  }

  fclose(file);
  free(Sigma);
  freeVect(vectFinaux);
  freeVect(vectInitiaux);

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

Vect *afn_epsilon_fermeture(AFN A, Vect *R) {

  Vect *fermeture = createVect(true);
  
  if (R == NULL) {
    return fermeture;
  }

  Stack *stack = createStack();

  for (int index = 0; index < R->size; index++) {
    push(stack, vectGet(R, index));
    vectAdd(fermeture, vectGet(R, index));
  }

  int epsilonLetter = A->dico['&'-ASCII_FIRST];
  while (!stackIsEmpty(stack)) {
    int q = pop(stack);
    Vect *delta = vectArrayGet(A->delta[q], epsilonLetter);
    if (delta != NULL) {
      for (int index = 0; index < delta->size; index++) {
        int q_sec = vectGet(delta, index);
        if (!vectContrainsValue(fermeture, q_sec)) {
          vectAdd(fermeture, q_sec);
          push(stack, q_sec);
        }
      }
    }
  }
  freeStack(stack);
  return fermeture;
}

/**
 * @brief Permet de convertir un AFN en son AFD.
 * 
 * @param A un AFN
 * @return AFD l'AFD correspondant à la déterminisation de l'AFN A
 */
AFD afn_determiniser(AFN A) {
  Vect *Q_0 = afn_epsilon_fermeture(A, A->I);

  // Ensemble d'ensemble, correspond à la colonne gauche
  // de la table de déterminisation
  VectArray *S = createVectArray();
  vectArrayAdd(S, Q_0);

  Vect *finaux = createVect(false);

  Vect *stateQ0 = createVect(false);
  Vect *stateSymb = createVect(false);
  Vect *stateQ1 = createVect(false);

  for (int sCursor = 0; sCursor < S->size; sCursor++) {
    Vect *setOfState = vectArrayGet(S, sCursor);
    for (int indexAlphabet = 1; indexAlphabet < A->lenSigma; indexAlphabet++) {
      char letter = A->Sigma[indexAlphabet];
      int letterInt = A->dico[letter-ASCII_FIRST];

      // Tous les états atteints seront stocké dans stateReached
      Vect *stateReached = createVect(true);
      bool addedInS = false;

      for (int stateCursor = 0; stateCursor < setOfState->size; stateCursor++) {
        int q = vectGet(setOfState, stateCursor);
        Vect *tmp = afn_epsilon_fermeture(A, vectArrayGet(A->delta[q], letterInt));
        unionVectAsSet(stateReached, tmp);
        freeVect(tmp);
      }
      
      int index = getIndexOfVectInVectArray(S, stateReached);
      
      // Si stateReached (vecteur calculé) n'appartient pas à S, on l'ajoute dans S
      if (index == -1) {
        index = S->size;
        vectArrayAdd(S, stateReached);
        addedInS = true;
      }

      // On ajoute les morceaux de transition pour la construire plus tard, après
      // avoir initialisé l'AFD
      vectAdd(stateQ0, sCursor);
      vectAdd(stateSymb, letter);
      vectAdd(stateQ1, index);

      // Ajout des états finaux
      for (int stateReachedIndex = 0; stateReachedIndex < stateReached->size; stateReachedIndex++) {
        int state = vectGet(stateReached, stateReachedIndex);
        if (vectContrainsValue(A->F, state) && !vectContrainsValue(finaux, index)) {
          vectAdd(finaux, index);
          break;
        }
      }
      
      // Si le vecteur généré est déjà dans S, on l'a crée pour rien, on peut le supprimer définitivement
      if (!addedInS) {
        freeVect(stateReached);
      }
    }
  }

  char *newSigma = AFNSigmaToAFDSigma(A);

  AFD B = afd_init(S->size - 1, 0, finaux, newSigma);

  for (int i = 0; i < stateQ0->size; i++) {
    afd_ajouter_transition(B, vectGet(stateQ0, i), vectGet(stateSymb, i), vectGet(stateQ1, i));
  }

  freeVect(stateQ0);
  freeVect(stateSymb);
  freeVect(stateQ1);
  freeVect(finaux);
  free(newSigma);

  for (int i = 0; i < S->size; i++) {
    freeVect(S->array[i]);
  }
  freeVectArray(S);

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
int afn_simuler(AFN A, char *s) {
  AFD afd = afn_determiniser(A);
  int res = afd_simuler(afd, s);
  afd_free(afd);
  return res;


  /*
  Vect *R = afn_epsilon_fermeture(A, A->I);
 
  for (int alphabetIndex = 0; alphabetIndex < A->lenSigma; alphabetIndex++) {
    char letter = A->Sigma[alphabetIndex];
    int letterInt = A->dico[letter-ASCII_FIRST];

    Vect *tmp = createVect(true);
    for (int q = 0; q < A->Q + 1; q++) {
      unionVectAsSet(tmp, afn_epsilon_fermeture(A, vectArrayGet(A->delta[q], letterInt)));
    }
    freeVect(R);
    R = tmp;
  }

  return intersectionOfVectIsNotEmpty(R, A->F);
  */
}

/**
 * @brief Permet de convertir l'alpabet d'un AFN en l'alphabet d'un AFD. (retire le caractère vide epsilon)
 * 
 * @param A l'AFN
 * @return char* le nouvel alphabet
 */
char *AFNSigmaToAFDSigma(AFN A) {
  char *newSigma = (char *) malloc(sizeof(char) * A->lenSigma);
  throwMallocErrorIfTrue(newSigma == NULL);
  for (int i = 0; i < A->lenSigma - 1; i++) {
    newSigma[i] = A->Sigma[i + 1];
  }
  newSigma[A->lenSigma - 1] = '\0';
  return newSigma;
}

/**
 * @brief Crée une image à partir d'un AFN.
 * L'image créée sera placée dans le dossier ./data/graphViz/png/fileName.png
 * L'image est créée à l'aide du module graphViz
 * 
 * @param A un AFN
 * @param fileName le nom donné au fichier crée
 */
void afn_toPng(AFN A, char *fileName) {
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
  for (int i = 0; i < A->I->size; i++) {
    graphVizAddInitialState(file, vectGet(A->I, i));
  }

  // Add final state
  for (int i = 0; i < A->F->size; i++) {
    graphVizAddFinalState(file, vectGet(A->F, i));
  }

  // Add transitions
  for (int q = 0; q < A->Q + 1; q++) {
    for (int alphabetIndex = 0; alphabetIndex < A->lenSigma; alphabetIndex++) {
      char letter = A->Sigma[alphabetIndex];
      Vect *vect = vectArrayGet(A->delta[q], alphabetIndex);
      if (vect != NULL) {
        for (int i = 0; i < vect->size; i++) {
          int q2 = vectGet(vect, i);
          graphVizAddTransition(file, q, letter, q2);
        }
      }
    }
  }

  graphVizEnd(file);
  fclose(file);

  char cmd[512];
  sprintf(cmd, "dot -Tpng %s > %s", destinationDotFile, destinationPngFile);
  system(cmd);

}

/**
 * @brief Permet de "verser" l'ensemble des transitions d'un AFN dans un autre AFN en lui ajoutant un décalage
 * 
 * @param from l'AFN qui recevra les transitions
 * @param to l'AFN qui donnera ses transitions
 * @param shift décalage des états
 * 
 * @see afn_union, afn_concat
 */
void afn_spill_transitions(AFN from, AFN to, int shift) {
  for (int q = 0; q < from->Q + 1; q++) {
    for (int alphabetIndex = 0; alphabetIndex < from->lenSigma; alphabetIndex++) {
      char letter = from->Sigma[alphabetIndex];

      Vect *vect = vectArrayGet(from->delta[q], alphabetIndex);
      if (vect != NULL) {
        for (int q2Index = 0; q2Index < vect->size; q2Index++) {
          afn_ajouter_transition(to, q + shift, letter, vectGet(vect, q2Index) + shift);
        }
      }
    }
  }
}

/**
 * @brief Crée un AFN acceptant le langage constitué du seul symbole c.
 * 
 * @param C l'AFN qui acceptera le langage
 * @param c caractère accepté
 */
void afn_char(AFN *C, char c) {
  Vect *initiaux = createVect(false);
  vectAdd(initiaux, 0);

  Vect *finaux = createVect(false);
  vectAdd(finaux, 1);

  char sigma[2];
  sprintf(sigma, "%c", c); 

  *C = afn_init(1, initiaux, finaux, sigma);
  afn_ajouter_transition(*C, 0, c, 1);

  freeVect(initiaux);
  freeVect(finaux);
}

/**
 * @brief Construit l'AFN reconnaissant l'union des langages acceptés par les automates A et B.
 * 
 * @param C l'AFN qui acceptera le langage
 * @param A AFN
 * @param B AFN
 */
void afn_union(AFN *C, AFN A, AFN B) {

  // construction des états initiaux
  Vect *initiaux = createVect(false);
  vectAdd(initiaux, 0);

  // construction des états finaux
  Vect *finaux = createVect(false);
  for (int i = 0; i < A->F->size; i++) {
    vectAdd(finaux, vectGet(A->F, i) + 1);
  }
  for (int i = 0; i < B->F->size; i++) {
    vectAdd(finaux, vectGet(B->F, i) + A->Q + 2);
  }

  char *CSigma = unionCharArray(A->Sigma, A->lenSigma, B->Sigma, B->lenSigma);

  // Création AFN
  *C = afn_init(A->Q + B->Q + 2, initiaux, finaux, CSigma);

  // Ajout des transitions dûes à l'union
  for (int i = 0; i < A->I->size; i++) {
    afn_ajouter_transition(*C, 0, '&', vectGet(A->I, i) + 1);
  }
  for (int i = 0; i < B->I->size; i++) {
    afn_ajouter_transition(*C, 0, '&', vectGet(B->I, i) + A->Q + 2);
  }

  // Ajout des transitions de A dans C
  afn_spill_transitions(A, *C, 1);

  // Ajout des transitions de B dans C
  afn_spill_transitions(B, *C, A->Q + 2);

  free(CSigma);
  freeVect(initiaux);
  freeVect(finaux);
}

/**
 * @brief Construit l'AFN reconnaissant la concaténation des langages acceptés par les automates A et B.
 * 
 * @param C l'AFN qui acceptera le langage
 * @param A AFN
 * @param B AFN
 */
void afn_concat(AFN *C, AFN A, AFN B) {
  Vect *finaux = createVect(false);
  for (int i = 0; i < B->F->size; i++) {
    vectAdd(finaux, vectGet(B->F, i) + A->Q + 1);
  }

  char *CSigma = unionCharArray(A->Sigma, A->lenSigma, B->Sigma, B->lenSigma);

  *C = afn_init(A->Q + B->Q + 1, A->I, finaux, CSigma);

  // Ajout des transitions de A dabs C
  afn_spill_transitions(A, *C, 0);

  // Ajout des transitions de B dans C
  afn_spill_transitions(B, *C, A->Q + 1);

  for (int indexFinauxA = 0; indexFinauxA < A->F->size; indexFinauxA++) {
    int qFinalA = vectGet(A->F, indexFinauxA);
    for (int indexInitB = 0; indexInitB < B->I->size; indexInitB++) {
      int qInitB = vectGet(B->I, indexInitB);
      afn_ajouter_transition(*C, qFinalA, '&', qInitB + A->Q +1);
    }
  }

  free(CSigma);
  freeVect(finaux);
}

/**
 * @brief Construit l'AFN reconnaissant la fermeture de Kleene des langages acceptés par les automates A et B.
 * 
 * @param C l'AFN qui acceptera le langage
 * @param A AFN
 */
void afn_kleene(AFN *C, AFN A) {

  Vect *initiaux = createVect(false);
  vectAdd(initiaux, 0);

  Vect *finaux = createVect(false);
  vectAdd(finaux, 1 + A->Q + 1);

  *C = afn_init(A->Q + 2, initiaux, finaux, A->Sigma);

  // Ajout des transitions de A vers C
  afn_spill_transitions(A, *C, 1);

  for (int i = 0; i < A->I->size; i++) {
    afn_ajouter_transition(*C, 0, '&', vectGet(A->I, i) + 1);
  }

  for (int i = 0; i < A->F->size; i++) {
    afn_ajouter_transition(*C, vectGet(A->F, i) + 1, '&', A->Q + 2);
    for (int j = 0; j < A->I->size; j++) {
      afn_ajouter_transition(*C, vectGet(A->F, i) + 1, '&', vectGet(A->I, j) + 1);
    }
  }

  afn_ajouter_transition(*C, 0, '&', A->Q + 2);

  freeVect(initiaux);
  freeVect(finaux);

}