%{
  #include <stdio.h>
  #include <ctype.h>
  #include <unistd.h>

  #include "asa.h"
  #include "ts.h"

  extern int yylex();

%}

%union{
  int nb;
  char id[32];
  struct asa * noeud;
 };

%define parse.error verbose

%token DEBUT FIN PLUS MOINS MULT DIV FTQ INF INF_EGAL SUP SUP_EGAL PAR_L PAR_R AFFECT END_INSTRUCT AFFICHER VAR TQ NOT_EGAL FAIRE
%token <nb> NB
%token <id> ID

%type <noeud> INSTRUCT EXP INSTRUCTS LVALUE

%precedence AFFECT
%left EGAL NOT_EGAL INF INF_EGAL SUP SUP_EGAL
%left PLUS MOINS
%left MULT DIV

%start PROG

%%

PROG : DEBUT INSTRUCTS FIN {codegen($2); fprintf(ramFile, "STOP");}
;

INSTRUCTS : INSTRUCTS INSTRUCT {$$ = union_noeud($1, $2);}
| INSTRUCT {$$ = union_noeud(NULL, $1);}
;

INSTRUCT : EXP END_INSTRUCT {$$ = $1;}
| AFFICHER EXP END_INSTRUCT {$$ = creer_noeudAfficher($2);}
| VAR ID END_INSTRUCT { $$ = creer_noeudCreerId($2);}
| TQ EXP FAIRE INSTRUCTS FTQ {$$ = creer_noeudTQ($2, $4); }
//| SI EXP ALORS INSTRUCTS FSI {}
//| SI EXP ALORS INSTRUCTS SINON INSTRUCTS FSI {}
;

EXP : EXP PLUS EXP { $$ = creer_noeudOp('+', $1, $3); }
| EXP MOINS EXP { $$ = creer_noeudOp('-', $1, $3); }
| EXP MULT EXP { $$ = creer_noeudOp('*', $1, $3); }
| EXP DIV EXP { $$ = creer_noeudOp('/', $1, $3); }
| PAR_L EXP PAR_R { $$ = $2;}
| EXP EGAL EXP { $$ = creer_noeudEgal($1, $3); }
| EXP INF EXP { $$ = creer_noeudInf($1, $3); } // todo
| EXP INF_EGAL EXP { $$ = creer_noeudInfEgal($1, $3); } // todo
| EXP SUP EXP { $$ = creer_noeudSup($1, $3); } // todo
| EXP SUP_EGAL EXP { $$ = creer_noeudSupEgal($1, $3); } // todo
| EXP NOT_EGAL EXP { $$ = creer_NoeudNotEgal($1, $3); } // todo
| LVALUE AFFECT EXP { $$ = creer_noeudAffect($1, $3); }
| ID { $$ = creer_feuilleID($1); }
| NB { $$ = creer_feuilleNb($1); }
;

LVALUE: ID { $$ = creer_feuilleID($1); };

%%

int main( int argc, char * argv[] ) {

  extern FILE *yyin;
  if (argc == 1){
    fprintf(stderr, "Veuillez préciser le fichier source pseudo-code \".psc\"\n");
    return 1;
  }

  extern FILE *ramFile;
  if (argc == 2) {
    fprintf(stderr, "Veuillez préciser le nom du fichier destination \".ram\"\n");
    return 1;
  }

  yyin = fopen(argv[1],"r");
  ramFile = fopen(argv[2], "w");

  extern ts table;
  table = ts_init_table("?");

  yyparse();

  fclose(yyin);
  fclose(ramFile);
  return 0;
}
