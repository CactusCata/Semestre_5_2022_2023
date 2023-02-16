#ifndef ASA_UTILS_H
#define ASA_UTILS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"

typedef enum {
    typeNb,
    typeId,
    typeOp,
    typeMoinsExpr,
    typeAfficher,
    typeLire,
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
    typeIf,
    typeIfElse,
    typeTq,
    typeCreerTableau,
    typeTableauAffect,
    typeTableauValeur
} typeNoeud;

// Definition des structures de noeuds
typedef struct {
  int val;
} feuilleNb;

typedef struct {
  char identificateur[32];
} feuilleId;

typedef struct {
  int ope;
  struct asa * noeud[2];
} noeudOp;

typedef struct {
  struct asa *expression;
} noeudMoinsExpr;

typedef struct {
  struct asa *noeud;
} noeudAfficher;

typedef struct {
  char identificateur[32];
} noeudLire;

typedef struct {
  char identificateur[32];
} noeudCreerId;

typedef struct {
  char identificateur[32];
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
  struct asa *condition;
  struct asa *instructions;
} noeudIf;

typedef struct {
  struct asa *condition;
  struct asa *instructionsIf;
  struct asa *instructionsElse;
} noeudIfElse;

typedef struct {
  struct asa *expression;
  struct asa *instructs;
} noeudTq;

typedef struct {
  char identificateur[32];
  struct asa *expression;
} noeudCreerTableau;

typedef struct {
  char identificateur[32];
  struct asa *indexExpression;
  struct asa *expression;
} noeudTableauAffect;

typedef struct {
  char identificateur[32];
  struct asa *indexExpression;
} noeudTableauValeur;

// Definition de l'arbre
typedef struct asa{
  typeNoeud type;
  int ninst;


  union {
    feuilleNb nb;
    feuilleId id;
    noeudOp op;
    noeudMoinsExpr moinsExpr;
    noeudAfficher afficher;
    noeudLire lire;
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
    noeudIf nodeIf;
    noeudIfElse nodeIfElse;
    noeudTq tq;
    noeudCreerTableau creerTableau;
    noeudTableauAffect tableauAffect;
    noeudTableauValeur tableauValeur;
  };
} asa;

// fonction d'erreur utilisée également par Bison
void yyerror(const char * s);

#endif
