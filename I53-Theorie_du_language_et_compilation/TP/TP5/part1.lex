%{
    /* Prologue */
    # include <stdio.h>
    # include <string.h>
    int longmax = 0;
    int line = 0;
    int col = 0;
    long long int sommeEntier = 0;
    char motlepluslong [256];
%}
%option nounput
%option noinput
/* Definitions */
BLANC [ \t\n]
LIGNE {MOT}*\n
LETTRE [a-zA-Z]
MOT {LETTRE}+
NOMBRE -?[0-9]+ 
%%
{NOMBRE} {
    printf("Entier actuel: %lld (%s)\n", sommeEntier, yytext);
    sommeEntier += atoi(yytext);
}

{LIGNE} {
    line++;
    col = 0;
}

{MOT} {
    if (yyleng > longmax){
        longmax = yyleng;
        strcpy(motlepluslong, yytext);
        printf("%s à %d:%d\n", yytext, line, col);
    }
    col += yyleng;
}
{BLANC}
.
%%
int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez préciser un nom de fichier !\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Le fichier '%s' n'existe pas !\n", argv[1]);
        return 1;
    }

    yylex();
    printf("\nMot le plus long: %s, de longueur: %d \n", motlepluslong, longmax);
    printf("Somme des entiers: %lld\n", sommeEntier);
    return 0;
}