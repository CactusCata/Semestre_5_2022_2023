#include "asa_codegen.h"

void codegen(asa *p)
{

  if (p == NULL) {
    return;
  }
  
  int id, a;

  switch(p->type) {

  case typeNb:
    printf("Nombre détecté\n");

    LOAD_VALUE(p->nb.val);
    STORE(0);

    break;
  
  case typeId:
    printf("Chargement d'un id... (%s)\n", p->id.identificateur);

    LOAD_VARIABLE(p->id.identificateur);
    STORE(0);

    break;

  case typeCreerId:
    printf("Déclaration d'une variable (%s)\n", p->creerId.identificateur);

    addID(p->creerId.identificateur);

    break;

  case typeOp:
    printf("Operateur détecté\n");

    a = getCurrentStackCursor();
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);

    switch (p->op.ope) {
      case '+': ADD(-getCurrentStackCursor() + a); break;
      case '-': SUB(-getCurrentStackCursor() + a); break;
      case '*': MUL(-getCurrentStackCursor() + a); break;
      case '/': DIVI(-getCurrentStackCursor() + a); break;
      case '%': MOD(-getCurrentStackCursor() + a); break;
      default: fprintf(stderr, "Operation '%c' inconnue.\n", p->op.ope); exit(0);
    }
    setStackCursor(a);
    STORE(-getCurrentStackCursor() + a);
    break;

  case typeMoinsExpr:
    printf("-Expression détecté\n");

    codegen(p->moinsExpr.expression);
    MUL_VALUE(-1);
    STORE(-1);

    break;

  case typeAffect:
    codegen(p->affect.noeudExp);
    printf("Affectation à un id (%s)\n", p->affect.identificateur);
    STORE_VARIABLE(p->id.identificateur);
    break;

  case typeAfficher:
    codegen(p->afficher.noeud);
    printf("Affichage demandé\n");
    WRITE();
    break;

  case typeLire:
    printf("Demande de lecture\n");
    READ();
    STORE_VARIABLE(p->lire.identificateur);
    break;

  case typeUnion:
    printf("On est tombé sur un union\n");
    codegen(p->union_noeud.instructs);
    resetStackCursor();
    codegen(p->union_noeud.instruct);
    break;

  case typeEgal:
    printf("On est tombé sur un égal\n");

    a = getCurrentStackCursor();
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);

    SUB(-getCurrentStackCursor() + a);
    JUMZ(+3);

    LOAD_VALUE(0);
    JUMP(+2);

    LOAD_VALUE(1);
    setStackCursor(a);

    break;

  case typeNotEgal:
    printf("On est tombé sur un different\n");

    a = getCurrentStackCursor();
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);

    SUB(-getCurrentStackCursor() + a);
    JUMZ(+3);

    LOAD_VALUE(1);
    JUMP(+2);

    LOAD_VALUE(0);

    setStackCursor(a);

    break;

  case typeInf:
    printf("On est tombé sur un inferieur\n");

    a = getCurrentStackCursor();
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);

    SUB(-getCurrentStackCursor() + a);
    JUML(+3);

    LOAD_VALUE(0);
    JUMP(+2);

    LOAD_VALUE(1);

    setStackCursor(a);

    break;

  case typeInfEgal:
    printf("On est tombé sur un inférieur ou égal\n");

    a = getCurrentStackCursor();
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);

    SUB(-getCurrentStackCursor() + a);
    JUML(+4);
    JUMZ(+3);

    LOAD_VALUE(0);
    JUMP(+2);

    LOAD_VALUE(1);

    setStackCursor(a);

    break;

  case typeSup:
    printf("On est tombé sur un supérieur\n");

    a = getCurrentStackCursor();
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);

    SUB(-getCurrentStackCursor() + a);
    JUMG(+3);

    LOAD_VALUE(0);
    JUMP(+2);

    LOAD_VALUE(1);

    setStackCursor(a);

    break;

  case typeSupEgal:
    printf("On est tombé sur un supérieur ou égal\n");

    a = getCurrentStackCursor();
    codegen(p->op.noeud[1]);
    codegen(p->op.noeud[0]);

    SUB(-getCurrentStackCursor() + a);
    JUMG(+4);
    JUMZ(+3);

    LOAD_VALUE(0);
    JUMP(+2);

    LOAD_VALUE(1);

    setStackCursor(a);

    break;

  case typeAnd:
    printf("On est tombé sur un et\n");
    
    codegen(p->op.noeud[0]);

    // expression de gauche == 0 ?
    JUMZ(p->op.noeud[1]->ninst +5);
    codegen(p->op.noeud[1]);

    // expression de droite == 0 ?
    JUMZ(+3);

    // Si les deux tests passés, alors on met à 1 et on passe à la suite
    LOAD_VALUE(1);
    JUMP(+2);
    
    LOAD_VALUE(0);


    decrementStackCursor(1);
    decrementStackCursor(1);

    break;

  case typeOr:
    printf("On est tombé sur un ou\n");
    codegen(p->op.noeud[0]);

    // expression de gauche == 1 ? si oui on arrête la procedure
    JUMG(p->op.noeud[1]->ninst +7);
    JUML(p->op.noeud[1]->ninst +6);
    codegen(p->op.noeud[1]);
    JUMG(+4);
    JUML(+3);
    LOAD_VALUE(0);
    JUMP(+2);
    LOAD_VALUE(1);

    decrementStackCursor(1);
    decrementStackCursor(1);

    break;

  case typeIf:

    printf("Condition if\n");

    codegen(p->nodeIf.condition);
    JUMZ(p->nodeIf.instructions->ninst + 1);
    codegen(p->nodeIf.instructions);


    break;

  case typeIfElse:

    printf("Condition if else");

    codegen(p->nodeIfElse.condition);
    JUMZ(p->nodeIfElse.instructionsIf->ninst + 2);

    // condition validée
    codegen(p->nodeIfElse.instructionsIf);
    JUMP(p->nodeIfElse.instructionsElse->ninst + 1);

    // condition non validée
    codegen(p->nodeIfElse.instructionsElse);


    break;

  case typeTq:
    printf("TQ\n");

    int numeroLigne = getCurrentLineCode();
    codegen(p->tq.expression);
    JUMZ(p->tq.instructs->ninst + 2);
    codegen(p->tq.instructs);
    JUMP(-getCurrentLineCode() + numeroLigne);
    break;

  case typeCreerTableau:
    // On place la valeur dans l'ACC
    printf("[typeCreerTableau] Codegen de l'expression...\n");
    codegen(p->creerTableau.expression);
    printf("[typeCreerTableau] Fin du codegen de l'expression.\n");
    printf("[typeCreerTableau] On stock le contenu de l'ACC\n");
    STORE(0);
    printf("[typeCreerTableau] création du tableau\n");
    creerTableau(p->creerTableau.identificateur);


    break;

  case typeTableauAffect:
    printf("Affect to array\n");


    codegen(p->tableauAffect.indexExpression);
    id = getID(p->tableauAffect.identificateur);
    
    ADD(-getCurrentStackCursor() + id);
    STORE(0); // en -2 se trouve la ligne qui contient la case tab[index]

    codegen(p->tableauAffect.expression);

    printf("%d:\tSTORE @%d\n", getCurrentLineCode(), getCurrentStackCursor() - 2);
    fprintf(ramFile, "STORE @%d\n", getCurrentStackCursor() - 2); increaseCodeLine();

    break;

  case typeTableauValeur:
    printf("Get valeur of array\n");
    
    codegen(p->tableauValeur.indexExpression);
    id = getID(p->tableauValeur.identificateur);
    ADD(-getCurrentStackCursor() + id);
    STORE(0);

    printf("%d:\tLOAD @%d\n", getCurrentLineCode(), getCurrentStackCursor() - 1);
    fprintf(ramFile, "LOAD @%d\n", getCurrentStackCursor() - 1); 
    increaseCodeLine();

    break;

  default:
    printf("Type de noeud inconnu. (%d)\n", p->type);
    break;
    }

}
