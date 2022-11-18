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
  struct asa * noeud;
 };

%define parse.error verbose

%token <nb> NB

%type <noeud> EXP

%left '+'

%start PROG

%%

PROG : ALGO INPUT CODE END { codegen($3); }
;

ALGO : 

EXP : NB                   { $$ = creer_feuilleNb(yylval.nb); } // $$ = creer_feuilleNb($1);
| EXP '+' EXP              { $$ = creer_noeudOp('+', $1, $3); }
|
;

%%

int main( int argc, char * argv[] ) {

  extern FILE *yyin;
  if (argc == 1){
    fprintf(stderr, "aucun fichier fournie\n");
    return 1;
  }
  yyin = fopen(argv[1],"r");
  yyparse();
  return 0;
}
