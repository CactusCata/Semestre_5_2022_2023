#include "asa.h"

asa * creer_feuilleNb(int val)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  printf("Creation d'une feuille nombre = %d\n", val);

  p->type = typeNb;
  p->next = NULL;
  p->nb.val = val;
  p->ninst = 1;
  return p;
}

asa * creer_feuilleID(char *identificateur)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  printf("Creation d'une feuille identifiant = %s\n", identificateur);

  p->type = typeId;
  p->next = NULL;
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
  p->next = NULL;
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

  printf("Creation d'un noeuf afficher\n");

  p->type = typeAfficher;
  p->next = NULL;
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
    p->next = NULL;
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

    printf("Creation d'un noeuf affectation (%s = ...)\n", identificateur);

    p->type = typeAffect;
    p->next = NULL;
    p->ninst = 1;
    p->affect.identificateur = (char *) malloc(sizeof(char) * 32);
    strcpy(p->affect.identificateur, identificateur);
    p->affect.noeudExp = noeudExp;

    return p;
}

asa * union_noeud(asa *instructs, asa *current)
{

    asa *tmp = instructs;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }

    tmp->next = current;

    return instructs;
    
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

/**
| ID AFFECT EXP {int id = ts_ajouter_id(table, $1); printf("STORE %d\n", id); cursorMemory--;}
| ID {int id = ts_retrouver_id(table, $1); printf("LOAD %d\nSTORE %d\n", id, cursorMemory); cursorMemory++;}
| NB {printf("LOAD #%d\nSTORE %d\n", $1, cursorMemory++);}
;

*/

FILE *ramFile;

int stackCursor = 1;
ts table;

// typedef enum {typeNb, typeId, typeOp, typeAfficher, typeCreerId, typeAffect} typeNoeud;
void codegen(asa *p)
{
  
  int id;

  while (p != NULL) { 
    switch(p->type) {

    case typeNb:
      printf("Nombre détecté\n");
      fprintf(ramFile, "LOAD #%d\n", p->nb.val);
      fprintf(ramFile, "STORE %d\n", stackCursor);
      stackCursor++;
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
      break;

    case typeAffect:
      codegen(p->affect.noeudExp);
      printf("Affectation à un id (%s)\n", p->affect.identificateur);
      id = ts_retrouver_id(table, p->id.identificateur); 
      fprintf(ramFile, "STORE %d\n", id);
      stackCursor--;
      break;

    case typeAfficher:
      codegen(p->afficher.noeud);
      printf("Affichage demandé\n");
      fprintf(ramFile, "WRITE\n");
      break;

    default:
      printf("Type de noeud inconnu.\n");
      break;
    }

    p = p->next;
  }
}



void yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  exit(0);
}
