%{

  #include <stdio.h>
  #include <ctype.h>
  #include <stdlib.h>
  #include <string.h>

  #include "ts.h"

  extern int yylex(); // Contenu dans le fichier lexer.h
  int yyerror(const char *msg);

  int cursorMemory = 1;
  ts table;

%}

%token DEBUT FIN PLUS MOINS MULT DIV PAR_L PAR_R AFFECT END_INSTRUCT AFFICHER SI ALORS FSI
%token <nb> NB
%token <id> ID

%right AFFECT
%left PLUS MOINS
%left MULT DIV

%start PROG

// Les valeurs prises par "yylval" en le remplacant
// Utilisation avec yylval.nb (celle comprise dans l'union)
// On ajoute
%union{
  int nb;
  char id[32];
 }

%%

PROG : DEBUT INSTRUCTS FIN       {printf("STOP\n");}
;

INSTRUCTS : INSTRUCTS INSTRUCT {}
| CONDITION {}
| INSTRUCT {}
;

INSTRUCT : EXP END_INSTRUCT {}
| AFFICHER EXP END_INSTRUCT {printf("WRITE\n");}
;

CONDITION : SI EXP ALORS INSTRUCTS FSI {};

EXP : EXP PLUS EXP {printf("ADD %d\nSTORE %d\n", cursorMemory - 2, cursorMemory - 2); cursorMemory--;}
| EXP MOINS EXP {printf("LOAD %d\nSUB %d\nSTORE %d\n", cursorMemory - 2, cursorMemory - 1, cursorMemory - 2); cursorMemory--;}
| EXP MULT EXP {printf("MUL %d\nSTORE %d\n", cursorMemory - 2, cursorMemory - 2); cursorMemory--;}
| EXP DIV EXP {printf("LOAD %d\nDIV %d\nSTORE %d\n", cursorMemory - 2, cursorMemory - 1, cursorMemory - 2); cursorMemory--;}
| PAR_L EXP PAR_R {}
| ID AFFECT EXP {int id = ts_ajouter_id(table, $1); printf("STORE %d\n", id); cursorMemory--;}
| ID {int id = ts_retrouver_id(table, $1); printf("LOAD %d\nSTORE %d\n", id, cursorMemory); cursorMemory++;}
| NB {printf("LOAD #%d\nSTORE %d\n", $1, cursorMemory++);}
;

%%

int main( int argc, char * argv[] ) {

  extern FILE * yyin;
  if (argc < 2){
    printf("usage: %s <file_name>\n",argv[0]);
    return 1;
  } else {

    if ( (yyin= fopen(argv[1],"r"))== NULL ){
      printf("Could not open file %s\n",argv[1]);
      return 1;
    }
  }
  table = ts_init_table("?");
  yyparse() ;
  ts_free_table(table);
  fclose(yyin);
  return 0;
}

int yyerror(const char *msg){
  fprintf(stderr,"%s\n",msg);
  return -1;
}
