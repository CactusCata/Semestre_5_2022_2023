%{
#include <string.h>
#include "parser.h"
%}

%option nounput
%option noinput

NOMBRE [0-9]+
IDENTIFICATEUR [a-zA-Z_][a-zA-Z0-9_]*
BLANC [ \t\n]
COMMENT #.*

%%

{BLANC}           { }

"DEBUT"           { return DEBUT; }
"FIN"             { return FIN; }
"AFFICHER"        { return AFFICHER; }
"VAR"             { return VAR; }
"SI"              { return SI; }
"ALORS"           { return ALORS; }
"SINON"           { return SINON; }
"FSI"             { return FSI; }
"TQ"              { return TQ; }
"FAIRE"           { return FAIRE; }
"FTQ"             { return FTQ; }
"LIRE"            { return LIRE; }

"+"               { return PLUS; }
"-"               { return MOINS; }
"*"               { return MULT; }
"/"               { return DIV; }
"%"               { return MODULO; }
"="               { return EGAL; }
"!="              { return NOT_EGAL; }
"<"               { return INF; }
"<="              { return INF_EGAL; }
">"               { return SUP; }
">="              { return SUP_EGAL; }

"OU"              { return OR; }
"ET"              { return AND; }

"["               { return SQUARE_BRACKET_L; }
"]"               { return SQUARE_BRACKET_R; }
"("               { return PAR_L; }
")"               { return PAR_R; }
"<-"              { return AFFECT; }
";"               { return END_INSTRUCT; }

{COMMENT}         { }


{NOMBRE}          { yylval.nb = atoi(yytext); return NB;}
{IDENTIFICATEUR}  { strcpy(yylval.id, yytext); return ID;}

.                 { fprintf(stderr, "[err lexer] caractere inconnu '%c'.\n",yytext[0]); return 1;}

%%
