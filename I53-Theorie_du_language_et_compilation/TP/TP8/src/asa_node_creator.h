#ifndef ASA_NODE_CREATOR_H
#define ASA_NODE_CREATOR_H

#include "asa_utils.h"
/*
  Les fonctions creer_<type> construise un noeud de l'arbre
  abstrait du type correspondant et renvoie un pointeur celui-ci
 */
asa * creer_feuilleNb( int value );
asa * creer_feuilleID( char *identificateur);
asa * creer_noeudOp( int ope, asa * p1, asa * p2 );
asa * creer_moins_unaire(asa *expression);
asa * creer_noeudAfficher(asa * afficher);
asa * creer_noeudLire(char *identificateur);
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
asa *creer_noeudIf(asa *condition, asa *instructions);
asa *creer_noeudIfElse(asa *condition, asa *instructionIf, asa *instructionElse);
asa *creer_noeudTQ(asa *expression, asa *instructs);
asa *creer_noeudCreerTableau(char *identificateur, asa *expression);
asa *creer_noeudTableauAffect(char *identificateur, asa *indexExpression, asa *expression);
asa *creer_noeudTableauValeur(char *identificateur, asa *indexExpression);

void free_asa(asa *p);

#endif