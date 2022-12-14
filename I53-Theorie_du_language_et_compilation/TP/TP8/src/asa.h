#ifndef ASA_H
#define ASA_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ts.h"

extern FILE *ramFile;
extern ts table;

typedef enum {
    typeNb,
    typeId,
    typeOp,
    typeAfficher,
    typeCreerId,
    typeAffect,
    typeUnion,
    typeNotEgal,
    typeEgal,
    typeInf,
    typeInfEgal,
    typeSup,
    typeSupEgal,
    typeAnd,
    typeOr,
    typeTq
} typeNoeud;

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

typedef struct {
  struct asa *instructs;
  struct asa *instruct;
} noeudUnion;

typedef struct {
  struct asa *noeud[2];
} noeudEgal;

typedef struct {
  struct asa *noeud[2];
} noeudNonEgal;

typedef struct {
  struct asa *noeud[2];
} noeudInf;

typedef struct {
  struct asa *noeud[2];
} noeudInfEgal;

typedef struct {
  struct asa *noeud[2];
} noeudSup;

typedef struct {
  struct asa *noeud[2];
} noeudSupEgal;

typedef struct {
  struct asa *noeud[2];
} noeudAnd;

typedef struct {
  struct asa *noeud[2];
} noeudOr;

typedef struct {
  struct asa *expression;
  struct asa *instructs;
} noeudTq;


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
    noeudUnion union_noeud;
    noeudEgal egal;
    noeudNonEgal nonEgal;
    noeudInf inf;
    noeudInfEgal infEgal;
    noeudSup sup;
    noeudSupEgal supEgal;
    noeudAnd and;
    noeudOr or;
    noeudTq tq;
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
asa * creer_noeudAffect(asa *noeudID, asa *noeudExp);
asa * union_noeud(asa *instructs, asa *current);
asa *creer_noeudEgal(asa *expr1, asa* expr2);
asa *creer_NoeudNotEgal(asa *expr1, asa *expr2);
asa *creer_noeudInf(asa *expr1, asa *expr2);
asa *creer_noeudInfEgal(asa *expr1, asa *expr2);
asa *creer_noeudSup(asa *expr1, asa *expr2);
asa *creer_noeudSupEgal(asa *expr1, asa *expr2);
asa *creer_noeudAnd(asa *expr1, asa *expr2);
asa *creer_noeudOr(asa *expr1, asa *expr2);
asa * creer_noeudTQ(asa *expression, asa *instructs);

void free_asa(asa *p);

// produit du code pour la machine RAM à partir de l'arbre abstrait
// ET de la table de symbole
void codegen(asa *p);


#endif
