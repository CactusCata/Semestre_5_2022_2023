#include "asa.h"

asa * creer_feuilleNb(int val)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  printf("Creation d'une feuille nombre = %d\n", val);

  p->type = typeNb;
  p->nb.val = val;
  p->ninst = 2;
  return p;
}

asa * creer_feuilleID(char *identificateur)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  printf("Creation d'une feuille identifiant = %s\n", identificateur);

  p->type = typeId;
  p->ninst = 2;
  p->id.identificateur = (char *) malloc(sizeof(char) * 32);
  strcpy(p->id.identificateur, identificateur);

  return p;
}

asa * creer_noeudOp( int ope, asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  printf("Creation d'un noeud operation = %c\n", ope);

  p->type = typeOp;
  p->op.ope = ope;
  p->op.noeud[0] = p1;
  p->op.noeud[1] = p2;
  p->ninst = p1->ninst + p2->ninst +2;

  return p;
}

asa * creer_noeudAfficher(asa * noeud)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  printf("Creation d'un noeud afficher\n");

  p->type = typeAfficher;
  p->ninst = 1;
  p->afficher.noeud = noeud;

  return p;
}

asa *creer_noeudCreerId(char *identificateur)
{
    asa *p;

    if ((p = malloc(sizeof(asa))) == NULL)
      yyerror("echec allocation mémoire");

    printf("Creation d'un id = %s\n", identificateur);
    p->type = typeCreerId;
    p->ninst = 0;
    p->creerId.identificateur = (char *) malloc(sizeof(char) * 32);
    strcpy(p->creerId.identificateur, identificateur);

    return p;
}

asa * creer_noeudAffect(char *identificateur, asa *noeudExp)
{
    asa *p;

    if ((p = malloc(sizeof(asa))) == NULL)
      yyerror("echec allocation mémoire");

    printf("Creation d'un noeud affectation (%s = ...)\n", identificateur);

    p->type = typeAffect;
    p->ninst = 1;
    p->affect.identificateur = (char *) malloc(sizeof(char) * 32);
    strcpy(p->affect.identificateur, identificateur);
    p->affect.noeudExp = noeudExp;

    return p;
}

asa * union_noeud(asa *instructs, asa *current)
{

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  printf("Creation d'un noeud union\n");

  p->type = typeUnion;
  p->union_noeud.instruct = current;
  p->union_noeud.instructs = instructs;
  p->ninst = (instructs == NULL ? 0 : instructs->ninst) + current->ninst;
  return p;

}

asa * creer_noeudTQ(asa *expression, asa *instructs); {

  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  printf("Creation d'un noeud tq\n");

  p->type = typeTq;
  p->ninst = 2 + expression.ninst + instructs.ninst;
  p->tq.expression = expression;
  p->tq.instructs = instructs;

}

// penser à faire les free des différents types de noeud ici
void free_asa(asa *p)
{

  if (!p) return;
  switch (p->type) {
  case typeOp:
    free_asa(p->op.noeud[0]);
    free_asa(p->op.noeud[1]);
    break;
  default: break;
  }
  free(p);
}

FILE *ramFile;

int stackCursor = 1;
int codeCursor = 0;
ts table;

// typedef enum {typeNb, typeId, typeOp, typeAfficher, typeCreerId, typeAffect} typeNoeud;
void codegen(asa *p)
{

  int id;

  if (p == NULL) {
    printf("est null\n");
    return;
  }

  switch(p->type) {

  case typeNb:
    printf("Nombre détecté\n");
    fprintf(ramFile, "LOAD #%d\n", p->nb.val);
    fprintf(ramFile, "STORE %d\n", stackCursor);
    stackCursor++;
    codeCursor += 2;
    break;

  case typeOp:
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);
    printf("Operateur détecté\n");

    switch (p->op.ope) {
      case '+': fprintf(ramFile, "ADD %d\n", stackCursor - 2); break;
      case '-': fprintf(ramFile, "SUB %d\n", stackCursor - 2); break;
      case '*': fprintf(ramFile, "MUL %d\n", stackCursor - 2); break;
      case '/': fprintf(ramFile, "DIV %d\n", stackCursor - 2); break;
      default: fprintf(stderr, "Operation '%c' inconnue.\n", p->op.ope); exit(0);
    }
    fprintf(ramFile, "STORE %d\n", stackCursor - 2);
    stackCursor--;
    codeCursor += 2;
    break;

  case typeCreerId:
    printf("Déclaration d'un variable\n");
    ts_ajouter_id(table, p->creerId.identificateur);
    break;

  case typeId:
    printf("Chargement d'un id... (%s)\n", p->id.identificateur);
    id = ts_retrouver_id(table, p->id.identificateur);
    fprintf(ramFile, "LOAD %d\n", id);
    fprintf(ramFile, "STORE %d\n", stackCursor);
    stackCursor++;
    codeCursor += 2;
    break;

  case typeAffect:
    codegen(p->affect.noeudExp);
    printf("Affectation à un id (%s)\n", p->affect.identificateur);
    id = ts_retrouver_id(table, p->id.identificateur);
    fprintf(ramFile, "STORE %d\n", id);
    codeCursor += 1;
    stackCursor--;
    break;

  case typeAfficher:
    codegen(p->afficher.noeud);
    printf("Affichage demandé\n");
    fprintf(ramFile, "WRITE\n");
    codeCursor += 1;
    break;

  case typeUnion:
    printf("On est tombé sur un union\n");
    codegen(p->union_noeud.instructs);
    codegen(p->union_noeud.instruct);
    break;

  case typeTq:
    int numeroLigne = codeCursor;
    codegen(p->tq.expression);
    fprintf(ramFile, "JMPZ %d\n", numeroLigne + p->ninst);
    codegen(p->tq.instructs);
    fprintf(ramFile, "JUMP %d\n", numeroLigne);
    break;

  default:
    printf("Type de noeud inconnu. (%d)\n", p->type);
    break;
    }

}

void yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  exit(0);
}
