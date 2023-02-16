%{
  #include <stdio.h>
  #include <ctype.h>
  #include <unistd.h>

  #include "asa_utils.h"
  #include "asa_node_creator.h"
  #include "asa_codegen.h"
  #include "ts.h"
  #include "instruction.h"

  extern int yylex();

%}

%union{
  int nb;
  char id[32];
  struct asa * noeud;
 };

%define parse.error verbose

%token DEBUT FIN PLUS MOINS MODULO MULT SQUARE_BRACKET_L SQUARE_BRACKET_R LIRE DIV FTQ SI ALORS SINON FSI OR AND INF INF_EGAL SUP SUP_EGAL PAR_L PAR_R AFFECT END_INSTRUCT AFFICHER VAR TQ NOT_EGAL FAIRE
%token <nb> NB
%token <id> ID

%type <noeud> INSTRUCT EXP INSTRUCTS LVALUE

%precedence AFFECT
%left EGAL NOT_EGAL INF INF_EGAL SUP SUP_EGAL
%left PLUS MOINS
%left MULT DIV
%left MODULO
%left AND
%left OR

%start PROG

%%

PROG : DEBUT INSTRUCTS FIN { initMemoryArrayCursor(); codegen($2); fprintf(ramFile, "STOP"); free_asa($2); }
;

INSTRUCTS : INSTRUCTS INSTRUCT {$$ = union_noeud($1, $2);}
| INSTRUCT {$$ = union_noeud(NULL, $1);}
;

INSTRUCT : EXP END_INSTRUCT {$$ = $1;}
| AFFICHER EXP END_INSTRUCT {$$ = creer_noeudAfficher($2);}
| LIRE ID END_INSTRUCT { $$ = creer_noeudLire($2);}
| VAR ID END_INSTRUCT { $$ = creer_noeudCreerId($2);}
| VAR ID SQUARE_BRACKET_L EXP SQUARE_BRACKET_R END_INSTRUCT { $$ = creer_noeudCreerTableau($2, $4); }
| TQ EXP FAIRE INSTRUCTS FTQ {$$ = creer_noeudTQ($2, $4); }
| SI EXP ALORS INSTRUCTS FSI {$$ = creer_noeudIf($2, $4); }
| SI EXP ALORS INSTRUCTS SINON INSTRUCTS FSI { $$ = creer_noeudIfElse($2, $4, $6); }
| ID SQUARE_BRACKET_L EXP SQUARE_BRACKET_R AFFECT EXP END_INSTRUCT { $$ = creer_noeudTableauAffect($1, $3, $6); }
;

EXP : EXP PLUS EXP { $$ = creer_noeudOp('+', $1, $3); }
| EXP MOINS EXP { $$ = creer_noeudOp('-', $1, $3); }
| EXP MULT EXP { $$ = creer_noeudOp('*', $1, $3); }
| EXP DIV EXP { $$ = creer_noeudOp('/', $1, $3); }
| EXP MODULO EXP { $$ = creer_noeudOp('%', $1, $3); }
| PAR_L EXP PAR_R { $$ = $2;}
| EXP EGAL EXP { $$ = creer_noeudEgal($1, $3); }
| EXP INF EXP { $$ = creer_noeudInf($1, $3); }
| EXP INF_EGAL EXP { $$ = creer_noeudInfEgal($1, $3); }
| EXP SUP EXP { $$ = creer_noeudSup($1, $3); }
| EXP SUP_EGAL EXP { $$ = creer_noeudSupEgal($1, $3); }
| EXP NOT_EGAL EXP { $$ = creer_NoeudNotEgal($1, $3); }
| EXP OR EXP { $$ = creer_noeudOr($1, $3); }
| EXP AND EXP { $$ = creer_noeudAnd($1, $3); }
| ID SQUARE_BRACKET_L EXP SQUARE_BRACKET_R { $$ = creer_noeudTableauValeur($1, $3); }
| LVALUE AFFECT EXP { $$ = creer_noeudAffect($1, $3); }
| ID { $$ = creer_feuilleID($1); }
| MOINS EXP { $$ = creer_moins_unaire($2); }
| NB { $$ = creer_feuilleNb($1); }
;

LVALUE: ID { $$ = creer_feuilleID($1); };

%%

int main( int argc, char * argv[] ) {

  extern FILE *yyin;
  if (argc == 1){
    fprintf(stderr, "Veuillez préciser le nom d'un fichier source pseudo-code \".psc\"\n");
    return 1;
  }

  extern FILE *ramFile;

  char psc_file_path[255];
  char ram_file_path[255];
  sprintf(psc_file_path, "./data/psc/%s.psc", argv[1]);
  sprintf(ram_file_path, "./data/ram/%s.ram", argv[1]);

  yyin = fopen(psc_file_path,"r");

  if (yyin == NULL) {
    printf("The file \"%s\" do not exist.\n", psc_file_path);
    return 1;
  }

  ramFile = fopen(ram_file_path, "w");

  extern ts table;
  table = ts_init_table("?");

  yyparse();

  freeTable();
  fclose(yyin);
  fclose(ramFile);
  return 0;
}