#include "afd.h"

void afd_init(afd *A, uint nbetat, char * alphabet, uint nbfinal, uint init, uint *finals)
{
  int i, nbsymb=0;
  uchar symb;

  A->nbetat = nbetat;
  A->nbfinal = nbfinal;
  A->init = init;

  for (i=0; i<SYMB_ASCII_FIN; i++)
    A->tsymb[i] = SYMB_NONE;

  A->alphabet = malloc(strlen(alphabet)+1);
  strcpy(A->alphabet, alphabet);
  A->nbsymb = strlen(alphabet);

  while (*alphabet != '\0'){

    if ( (*alphabet < SYMB_ASCII_DEB) ||
	 (*alphabet > SYMB_ASCII_FIN) ){
      fprintf(stderr,"[afd_init] caractere ascii numero %d invalide\n", *alphabet);
      exit(-1);
    }

    symb = (uchar) (*alphabet);
    if ( A->tsymb[symb] != SYMB_NONE ){
      fprintf(stderr,"[afd_init] caractere <%c> deja defini (ignorer)\n",symb);
    }
    else {
      A->tsymb[symb] = nbsymb;
      nbsymb++;
    }
    alphabet++;
  }

  A->finals = calloc(nbfinal, sizeof(uint));
  for (i=0; i < nbfinal; i++){
    A->finals[i] = finals[i];
  }

  int j;
  A->delta = calloc(nbetat, sizeof(uint *));
  for (i=0; i<nbetat; i++){
    A->delta[i] = calloc(A->nbsymb, sizeof(uint));
    for (j=0; j<A->nbsymb; j++)
      A->delta[i][j] = ETAT_NONE;
  }
}

void afd_free(afd *A)
{
  int i;
  free(A->finals);
  free(A->alphabet);
  for (i=0; i<A->nbetat; i++)
    free(A->delta[i]);
  free(A->delta);
}

void afd_add_trans(afd *A, uint q1, uint s, uint q2)
{
  uchar symb = A->tsymb[s];

  if (symb == SYMB_NONE){
    fprintf(stderr, "[add_trans] %u -- %c --> %u\n", q1,s,q2);
    exit(-1);
  }

  if ( (q1<0) || (q1>=A->nbetat) ){
   fprintf(stderr, "[add_trans] etat <%d> non reconnu\n", q1);
    exit(-1);
  }
  if ( (q2<0) || (q2>=A->nbetat) ){
   fprintf(stderr, "[add_trans] etat <%d> non reconnu\n", q2);
    exit(-1);
  }

  A->delta[q1][symb] = q2;
}

void afd_copy(afd *dest, afd *src)
{
  dest->nbetat = src->nbetat;
  dest->nbsymb = src->nbsymb;
  dest->nbfinal = src->nbfinal;
  dest->init = src->init;

  dest->alphabet = calloc(src->nbsymb, sizeof(char));
  strcpy(dest->alphabet, src->alphabet);

  memcpy(dest->tsymb, src->tsymb,SYMB_ASCII_FIN);

  int size = (src->nbetat-1)/ULLONG_BIT+1;
  dest->finals = calloc(sizeof(ullong),size);
  memcpy(dest->finals, src->finals, sizeof(ullong)*size);

  int i;
  dest->delta = calloc(src->nbetat, sizeof(uint *));
  for (i=0; i<src->nbetat; i++){
    dest->delta[i] = calloc(src->nbsymb, sizeof(uint));
    memcpy(dest->delta[i], src->delta[i], sizeof(uint)*src->nbsymb);
  }
}

void afd_print(afd A)
{
  int i;

  printf("etat initial: %d\n", A.init);
  printf("etats finals:");

  for (i=0; i< A.nbfinal; i++){
    printf(" %u", A.finals[i]);
    }
  printf("\n");

  uint q;
  int printed;

  for (q=0; q<A.nbetat; q++){
    printed = 0;
    for (i=0; i<A.nbsymb; i++){

      if (A.delta[q][i]!=ETAT_NONE){
	if (printed==1)
	  printf("    ");
	else
	  printf("%4u", q);
	printf(" -- %c --> %u\n", A.alphabet[i], A.delta[q][i]);
	printed=1;
      }
    }
    //if (printed==0) printf("\n");
  }
}

/*
  Initialise l'afd `A` à partir des données du fichier
  `nomfichier`
*/
void afd_finit(afd *A, char *nomfichier){
  FILE *file = fopen(nomfichier, "r");

  if (!file) {
    printf("Le fichier '%s' n'a pas été trouvé.\n", nomfichier);
    exit(1);
  }

  uint nbetat;
  char *alphabet;
  uint nbfinal;
  uint init;

  fscanf(file, "%u %ms %u\n", &nbetat, &alphabet, &nbfinal);
  fscanf(file, "%u\n", &init);

  char lineTextBuffer[1024];
  fgets(lineTextBuffer, 1024, file);

  uint *finals = str_splitInt(lineTextBuffer, ' ', nbfinal);

  afd_init(A, nbetat, alphabet, nbfinal, init, finals);

  while (fgets(lineTextBuffer, 1024, file)) {
    uint q1, q2;
    char s;
    sscanf(lineTextBuffer, "%u %c %u\n", &q1, &s, &q2);
    afd_add_trans(A, q1, s, q2);
  }

  fclose(file);

}

uint* str_splitInt(char* a_str, const char a_delim, uint count) {
    uint* result = (uint *) malloc(sizeof(char) * count);

    if (result) {
      char* token = strtok(a_str, &a_delim);
      uint index = 0;
      while (token) {
        uint res;
        sscanf(token, "%u", &res);
        result[index] = res;
        token = strtok(NULL, &a_delim);
        index++;
      }
    }

    return result;
}

/*
  Renvoie 1 si la chaine `s` est acceptée par l'automate
  `A` 0 sinon
*/
int afd_simul(char *s, afd A){

  uint etatCourant = A.init;
  uchar currentChar = *s;
  while (*s != '\0') {
    uint etatSuivant = A.delta[etatCourant][A.tsymb[currentChar]];

    if (etatSuivant == ETAT_NONE) {
      break;
    }

    currentChar = *(s++);
    etatCourant = etatSuivant;
  }

  for (uint i = 0; i < A.nbfinal; i++) {
    uint etatFinal = A.finals[i];
    if (etatCourant == etatFinal) {
      return 1;
    }
  }

  return 0;
 }
