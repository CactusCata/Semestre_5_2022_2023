#include "asa.h"

asa * creer_feuilleNb(int val)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeNb;
  p->nb.val = val;
  p->ninst = 1;
  return p;
}

asa * creer_feuilleID(char *identificateur)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeId;
  p->ninst = 0; // Peut etre autre chose
  p->id.identificateur = identificateur;

  return p;
}

asa * creer_noeudOp( int ope, asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

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

  p->type = typeAfficher;
  p->afficher.noeud = noeud;

  return p;
}

asa *creer_noeudCreerId(char *identificateur)
{
    asa *p;

    if ((p = malloc(sizeof(asa))) == NULL)
      yyerror("echec allocation mémoire");

    p->type = typeCreerId;
    p->ninst = 0;
    p->creerId.identificateur = identificateur;

    return p;
}

asa * creer_noeudAffect(char *identificateur, asa *noeudExp)
{
    asa *p;

    if ((p = malloc(sizeof(asa))) == NULL)
      yyerror("echec allocation mémoire");

    p->type = typeAffect;
    p->ninst = 1; // nombre d'instruction de la machine RAM pour charger un identifiant (vaut peut-être une autre valeur)
    p->affect.identificateur = identificateur;
    p->affect.noeudExp = noeudExp;

    return p;
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

EXP : EXP PLUS EXP {printf("ADD %d\nSTORE %d\n", cursorMemory - 2, cursorMemory - 2); cursorMemory--;}
| EXP MOINS EXP {printf("LOAD %d\nSUB %d\nSTORE %d\n", cursorMemory - 2, cursorMemory - 1, cursorMemory - 2); cursorMemory--;}
| EXP MULT EXP {printf("MUL %d\nSTORE %d\n", cursorMemory - 2, cursorMemory - 2); cursorMemory--;}
| EXP DIV EXP {printf("LOAD %d\nDIV %d\nSTORE %d\n", cursorMemory - 2, cursorMemory - 1, cursorMemory - 2); cursorMemory--;}
| PAR_L EXP PAR_R {}
| ID AFFECT EXP {int id = ts_ajouter_id(table, $1); printf("STORE %d\n", id); cursorMemory--;}
| ID {int id = ts_retrouver_id(table, $1); printf("LOAD %d\nSTORE %d\n", id, cursorMemory); cursorMemory++;}
| NB {printf("LOAD #%d\nSTORE %d\n", $1, cursorMemory++);}
;

*/

int stackCursor = 1;

// typedef enum {typeNb, typeId, typeOp, typeAfficher, typeCreerId, typeAffect} typeNoeud;
void codegen(asa *p)
{

  if (!p) return;
  switch(p->type) {

  case typeNb:
    printf("Nombre détecté\n");
    fprintf(ramFile, "LOAD #%d\n", p->nb.val);
    fprintf(ramFile, "STORE #%d\n", stackCursor);
    stackCursor++;
    break;

  case typeOp:
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);
    printf("Operateur détecté\n");

    switch (p->op.ope) {
      case '+': fprintf(ramFile, "ADD %d\n", stackCursor - 2); break;
      case '-': fprintf(ramFile, "SUB %d\n", stackCursor - 2); break;
      case '*': fprintf(ramFile, "MULT %d\n", stackCursor - 2); break;
      case '/': fprintf(ramFile, "DIV %d\n", stackCursor - 2); break;
    }
    fprintf(ramFile, "STORE %d\n", stackCursor - 2);
    stackCursor--;
    break;
  default:
    break;
  }
}



void yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  exit(0);
}
