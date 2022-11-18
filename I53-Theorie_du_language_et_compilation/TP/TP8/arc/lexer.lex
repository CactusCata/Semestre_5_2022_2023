%{
#include <string.h>
#include "parser.h"
%}

%option nounput
%option noinput

ALGO_R ALGO
ENTREE_R ENTREE
DEBUT_R DEBUT
FIN_R FIN

VAR_R VAR
AFFECT <-
TQ_R TQ
FTQ_R FTQ
SI_R SI
FSI_R FSI
SINON_R SINON
AFFICHER_R AFFICHER

LETTER [a-zA-Z]
IDENTIFICATEUR [a-zA-Z_][a-zA-Z0-9_]*
NUMBER [1-9][0-9]*

%%

"+"       { return yytext[0];}
{LETTER}  { return yytext;}
{IDENTIFICATEUR} {return yytext;}
{NUMBER}  { yylval.nb = atoi(yytext); return NB;}
.         { fprintf(stderr, "[err lexer] caractere inconnu %c\n",yytext[0]); return 1;}

%%
