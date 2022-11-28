#ifndef ASA_H
#define ASA_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ts.h"

extern FILE *ramFile;
extern ts table;

typedef enum {typeNb, typeId, typeOp, typeAfficher, typeCreerId, typeAffect} typeNoeud;

// Definition des structures de noeuds
typedef struct {
  int val;
} feuilleNb;

typedef struct {
  char *identificateur;
} feuilleId;

typedef struct {
  int ope;
  struct asa * noeud[2];
} noeudOp;

typedef struct {
  struct asa *noeud;
} noeudAfficher;

typedef struct {
  char *identificateur;
} noeudCreerId;

typedef struct {
  char *identificateur;
  struct asa *noeudExp;
} noeudAffect;


// Definition de l'arbre
typedef struct asa{
  typeNoeud type;
  int ninst;

  union {
    feuilleNb nb;
    feuilleId id;
    noeudOp op;
    noeudAfficher afficher;
    noeudCreerId creerId;
    noeudAffect affect;
  };
} asa;

// fonction d'erreur utilisée également par Bison
void yyerror(const char * s);

/*
  Les fonctions creer_<type> construise un noeud de l'arbre
  abstrait du type correspondant et renvoie un pointeur celui-ci
 */
asa * creer_feuilleNb( int value );
asa * creer_feuilleID( char *identificateur);
asa * creer_noeudOp( int ope, asa * p1, asa * p2 );
asa * creer_noeudAfficher(asa * afficher);
asa * creer_noeudCreerId(char *identificateur);
asa * creer_noeudAffect(char *identificateur, asa *noeudExp);

void free_asa(asa *p);

// produit du code pour la machine RAM à partir de l'arbre abstrait
// ET de la table de symbole
void codegen(asa *p);


#endif
