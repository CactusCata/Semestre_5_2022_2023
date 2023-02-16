#include "asa_node_creator.h"

asa *createAsa() {
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  return p;
}

asa * creer_feuilleNb(int val)
{
  /**
   * @brief 5
   * 
   */
  asa *p = createAsa();

  printf("Creation d'une feuille nombre = %d\n", val);

  p->type = typeNb;
  p->nb.val = val;
  p->ninst = 2;
  return p;
}

asa * creer_feuilleID(char *identificateur)
{
  /**
   * @brief variable a
   * 
   */
  asa *p = createAsa();

  printf("Creation d'une feuille identifiant = %s\n", identificateur);

  p->type = typeId;
  p->ninst = 2;
  strcpy(p->id.identificateur, identificateur);

  return p;
}

asa *creer_noeudCreerId(char *identificateur)
{
  /**
   * @brief VAR identificateur
   * 
   */
    asa *p = createAsa();

    printf("Creation d'un id = %s\n", identificateur);
    p->type = typeCreerId;
    p->ninst = 0;
    strcpy(p->creerId.identificateur, identificateur);

    return p;
}

asa * creer_noeudOp( int ope, asa * p1, asa * p2)
{
  /**
   * @brief expression op expression
   * 
   */
  asa * p = createAsa();

  printf("Creation d'un noeud operation = %c\n", ope);

  p->type = typeOp;
  p->op.ope = ope;
  p->op.noeud[0] = p1;
  p->op.noeud[1] = p2;
  p->ninst = p1->ninst + p2->ninst + 2;

  return p;
}

asa *creer_moins_unaire(asa *expression) {
    /**
     * @brief -expression
     * 
     */

    asa *p = createAsa();

    printf("Création d'un -expression\n");
    
    p->type = typeMoinsExpr;
    p->moinsExpr.expression = expression;
    p->ninst = expression->ninst + 1;

    return p;
}

asa * creer_noeudAffect(asa *noeudID, asa *noeudExp)
{
  /**
   * @brief identificateur <- expression
   * 
   */
    asa *p = createAsa();

    printf("Creation d'un noeud affectation (%s = ...)\n", noeudID->id.identificateur);

    p->type = typeAffect;
    p->ninst = noeudExp->ninst + 1;
    strcpy(p->affect.identificateur, noeudID->id.identificateur);
    free(noeudID);
    p->affect.noeudExp = noeudExp;

    return p;
}

asa * creer_noeudAfficher(asa * noeud)
{
  /**
   * @brief Afficher expression
   * 
   */
  asa *p = createAsa();

  printf("Creation d'un noeud afficher\n");

  p->type = typeAfficher;
  p->ninst = noeud->ninst + 1;
  p->afficher.noeud = noeud;

  return p;
}

asa * creer_noeudLire(char *identificateur)
{
  /**
   * @brief READ
   * 
   */

  asa *p = createAsa();

  printf("Création d'un noeud lire\n");

  p->type = typeLire;
  strcpy(p->lire.identificateur, identificateur);
  p->ninst = 2;
  
  return p;
}

asa * union_noeud(asa *instructs, asa *current)
{
  /**
   * @brief instruction1; instructionj;
   * 
   */
  asa *p = createAsa();

  printf("Creation d'un noeud union\n");

  p->type = typeUnion;
  p->union_noeud.instruct = current;
  p->union_noeud.instructs = instructs;
  p->ninst = (instructs == NULL ? 0 : instructs->ninst) + current->ninst;
  return p;

}

asa *creer_noeudEgal(asa *expr1, asa* expr2) {
  /**
   * @brief expression = expression
   * 
   * Renvoie 1 si les deux valeurs sont égales
   * Renvoie 0 sinon 
   * 
   */

  asa *p = createAsa();

  printf("Creation d'un noeud egal\n");

  p->type = typeEgal;
  p->op.noeud[0] = expr1;
  p->op.noeud[1] = expr2;
  p->ninst = expr1->ninst + expr2->ninst + 5;

  return p;
}

asa *creer_NoeudNotEgal(asa *expr1, asa* expr2) {
  /**
   * @brief expression != expression
   * 
   * Renvoie 1 si les deux valeurs sont différentes
   * Renvoie 0 sinon 
   * 
   */

  asa *p = createAsa();

  printf("Creation d'un noeud !=\n");

  p->type = typeNotEgal;
  p->op.noeud[0] = expr1;
  p->op.noeud[1] = expr2;
  p->ninst = expr1->ninst + expr2->ninst + 5;

  return p;
}

asa *creer_noeudInf(asa *expr1, asa *expr2) {
  /**
   * @brief expression1 < expression2
   * 
   * Renvoie 1 si expression1 < expression2
   * Renvoie 0 sinon 
   * 
   */

  asa *p = createAsa();

  printf("Creation d'un noeud inférieur\n");

  p->type = typeInf;
  p->op.noeud[0] = expr1;
  p->op.noeud[1] = expr2;
  p->ninst = expr1->ninst + expr2->ninst + 5;

  return p;
}

asa *creer_noeudInfEgal(asa *expr1, asa *expr2) {
  /**
   * @brief expression1 <= expression2
   * 
   * Renvoie 1 si expression1 <= expression2
   * Renvoie 0 sinon 
   * 
   */
  asa *p = createAsa();

  printf("Creation d'un noeud inférieur ou egal\n");

  p->type = typeInfEgal;
  p->op.noeud[0] = expr1;
  p->op.noeud[1] = expr2;
  p->ninst = expr1->ninst + expr2->ninst + 6;

  return p;
}

asa *creer_noeudSup(asa *expr1, asa *expr2) {
  /**
   * @brief expression1 > expression2
   * 
   * Renvoie 1 si expression1 > expression2
   * Renvoie 0 sinon 
   * 
   */
  asa *p = createAsa();

  printf("Creation d'un noeud supérieur\n");

  p->type = typeSup;
  p->op.noeud[0] = expr1;
  p->op.noeud[1] = expr2;
  p->ninst = expr1->ninst + expr2->ninst + 5;

  return p;
}

asa *creer_noeudSupEgal(asa *expr1, asa *expr2) {
  /**
   * @brief expression1 >= expression2
   * 
   * Renvoie 1 si expression1 >= expression2
   * Renvoie 0 sinon 
   * 
   */
  asa *p = createAsa();

  printf("Creation d'un noeud supérieur ou egal\n");

  p->type = typeSupEgal;
  p->op.noeud[0] = expr1;
  p->op.noeud[1] = expr2;
  p->ninst = expr1->ninst + expr2->ninst + 6;

  return p;
}

asa *creer_noeudAnd(asa *expr1, asa *expr2) {
  /**
   * @brief expression1 et expression2
   * 
   * Renvoie 1 si expression1 et expression2
   * Renvoie 0 sinon 
   * 
   */
  asa *p = createAsa();

  printf("Creation d'un noeud et\n");

  p->type = typeAnd;
  p->op.noeud[0] = expr1;
  p->op.noeud[1] = expr2;
  p->ninst = expr1->ninst + expr2->ninst + 5;

  return p;
}

asa *creer_noeudOr(asa *expr1, asa *expr2) {
  /**
   * @brief expression1 ou expression2
   * 
   * Renvoie 1 si expression1 ou expression2
   * Renvoie 0 sinon 
   * 
   */
  asa *p = createAsa();

  printf("Creation d'un noeud ou\n");

  p->type = typeOr;
  p->op.noeud[0] = expr1;
  p->op.noeud[1] = expr2;
  p->ninst = expr1->ninst + expr2->ninst + 7;

  return p;
}

asa *creer_noeudIf(asa *condition, asa *instructions) {
  /**
   * @brief SI condition ALORS
   *    instructions
   *  FSI
   *  
   * 
   */

  asa *p = createAsa();

  p->type = typeIf;
  p->nodeIf.condition = condition;
  p->nodeIf.instructions = instructions;
  p->ninst = condition->ninst + instructions->ninst + 1;

  return p;
}

asa *creer_noeudIfElse(asa *condition, asa *instructionsIf, asa *instructionsElse) {
  /**
   * @brief SI condition ALORS
   *  instructionIf
   * SINON
   *  instructionElse
   * FSI
   * 
   */

  asa *p = createAsa();

  p->type = typeIfElse;
  p->nodeIfElse.condition = condition;
  p->nodeIfElse.instructionsIf = instructionsIf;
  p->nodeIfElse.instructionsElse = instructionsElse;
  p->ninst = condition->ninst + instructionsIf->ninst + instructionsElse->ninst + 2;

  return p;
}

asa * creer_noeudTQ(asa *expression, asa *instructs) {

  asa *p = createAsa();

  printf("Creation d'un noeud tq\n");

  p->type = typeTq;
  p->ninst = 2 + expression->ninst + instructs->ninst;
  p->tq.expression = expression;
  p->tq.instructs = instructs;

  return p;

}

asa *creer_noeudCreerTableau(char *identificateur, asa* expression) {
  asa *p = createAsa();

  printf("Création d'un noeud creer tableau\n");

  p->type = typeCreerTableau;
  strcpy(p->creerTableau.identificateur, identificateur);
  p->creerTableau.expression = expression;
  p->ninst = expression->ninst + 10;

  return p;
}

asa *creer_noeudTableauAffect(char *identificateur, asa *indexExpression, asa *expression) {
  asa *p = createAsa();

  printf("Création d'un noeud affection à un tableau\n");

  p->type = typeTableauAffect;
  p->ninst = indexExpression->ninst + expression->ninst + 3;
  strcpy(p->tableauAffect.identificateur, identificateur);
  p->tableauAffect.indexExpression = indexExpression;
  p->tableauAffect.expression = expression;

  return p;
}

asa *creer_noeudTableauValeur(char *identificateur, asa *indexExpression) {
  asa *p = createAsa();

  printf("Création d'un noeud valeur de tableau\n");

  p->type = typeTableauValeur;

  p->ninst = indexExpression->ninst + 3;
  strcpy(p->tableauValeur.identificateur, identificateur);
  p->tableauValeur.indexExpression = indexExpression;

  return p;
}

void free_asa(asa *p)
{

  if (!p) return;
  switch (p->type) {
  case typeOp:
    free_asa(p->op.noeud[0]);
    free_asa(p->op.noeud[1]);
    break;
  case typeNb:
    break;
  
  case typeId:
    break;

  case typeCreerId:
    break;

  case typeMoinsExpr:
    free_asa(p->moinsExpr.expression);
    break;

  case typeAffect:
    free_asa(p->affect.noeudExp);
    break;

  case typeAfficher:
    free_asa(p->afficher.noeud);
    break;

  case typeLire:
    break;

  case typeUnion:
    free_asa(p->union_noeud.instructs);
    free_asa(p->union_noeud.instruct);
    break;

  case typeEgal:
    free_asa(p->op.noeud[1]);
    free_asa(p->op.noeud[0]);
    break;

  case typeNotEgal:
    free_asa(p->op.noeud[1]);
    free_asa(p->op.noeud[0]);
    break;

  case typeInf:
    free_asa(p->op.noeud[1]);
    free_asa(p->op.noeud[0]);
    break;

  case typeInfEgal:
    free_asa(p->op.noeud[1]);
    free_asa(p->op.noeud[0]);
    break;

  case typeSup:
    free_asa(p->op.noeud[1]);
    free_asa(p->op.noeud[0]);
    break;

  case typeSupEgal:
    free_asa(p->op.noeud[1]);
    free_asa(p->op.noeud[0]);
    break;

  case typeAnd:
    free_asa(p->op.noeud[0]);
    free_asa(p->op.noeud[1]);
    break;

  case typeOr:
    free_asa(p->op.noeud[0]);
    free_asa(p->op.noeud[1]);
    break;

  case typeIf:
    free_asa(p->nodeIf.condition);
    free_asa(p->nodeIf.instructions);
    break;

  case typeIfElse:
    free_asa(p->nodeIfElse.condition);
    free_asa(p->nodeIfElse.instructionsIf);
    free_asa(p->nodeIfElse.instructionsElse);
    break;

  case typeTq:
    free_asa(p->tq.expression);
    free_asa(p->tq.instructs);
    break;

  case typeCreerTableau:
    free_asa(p->creerTableau.expression);
    break;

  case typeTableauAffect:
    free_asa(p->tableauAffect.indexExpression);
    free_asa(p->tableauAffect.expression);
    break;

  case typeTableauValeur:
    free_asa(p->tableauValeur.indexExpression);
    break;
  default: break;
  }
  free(p);
}