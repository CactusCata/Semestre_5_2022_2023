%{
#include <string.h>
#include "parser.h"
%}

%option nounput
%option noinput

NOMBRE [1-9][0-9]*
IDENTIFICATEUR [a-zA-Z_][a-zA-Z0-9_]*
BLANC [ \t\n]

%%

"DEBUT"           { return DEBUT; }
"FIN"             { return FIN; }
"AFFICHER"        { return AFFICHER; }
"VAR"             { return VAR; }
"TQ"              { return TQ; }
"FAIRE"           { return FAIRE; }
"FTQ"             { return FTQ; }

"+"               { return PLUS; }
"-"               { return MOINS; }
"*"               { return MULT; }
"/"               { return DIV; }
"="               { return EGAL; }
"!="              { return NOT_EGAL; }
"<"               { return INF; }
"<="              { return INF_EGAL; }
">"               { return SUP; }
">="              { return SUP_EGAL; }

"("               { return PAR_L; }
")"               { return PAR_R; }
"<-"              { return AFFECT; }
";"               { return END_INSTRUCT; }

{NOMBRE}          { yylval.nb = atoi(yytext); return NB;}
{IDENTIFICATEUR}  { strcpy(yylval.id, yytext); return ID;}
{BLANC}           { }

.                 { fprintf(stderr, "[err lexer] caractere inconnu %c\n",yytext[0]); return 1;}

%%
