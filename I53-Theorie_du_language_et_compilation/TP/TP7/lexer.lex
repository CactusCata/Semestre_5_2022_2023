%{
  /*Prologue*/
  #include <stdio.h>
  #include <string.h>
  #include "parser.h"

%}
%option nounput
%option noinput

NOMBRE                [1-9][0-9]*
IDENTIFICATEUR        [a-zA-Z][a-zA-Z0-9]*
BLANC                 [ \t\n]

%%

"DEBUT"                 { return DEBUT; }
"FIN"                   { return FIN; }
"AFFICHER"              { return AFFICHER; }
"SI"                    { return SI; }
"ALORS"                 { return ALORS; }
"FSI"                   { return FSI; }
"+"                     { return PLUS; }
"-"                     { return MOINS; }
"*"                     { return MULT; }
"/"                     { return DIV; }
"("                     { return PAR_L; }
")"                     { return PAR_R; }
"<-"                    { return AFFECT; }
";"                     { return END_INSTRUCT; }
{NOMBRE}                { yylval.nb = atoi(yytext); return NB;}
{IDENTIFICATEUR}        { strcpy(yylval.id, yytext); return ID;}
{BLANC}                 { }
.                       { printf("lexer error: caractère inconnu"); exit(1);}

%%
