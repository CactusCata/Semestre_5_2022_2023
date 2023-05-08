%{
    /* Prologue */
    # include <stdio.h>
    # include <string.h>
    int maxForCount = 0;
    char indentsTypes[256];
    int totalIndent = 0;

    char functionName[64];
    char functionFound = 0;
%}
%option nounput
%option noinput
/* Definitions */
IFELSE [ ]*(if|else).*\n
FOR [ ]*(for|while).*\n
FUNCTION .*[ ]*\(
BLANC [ \t\n]
%%
{IFELSE} {
    int tabAmount = 0;
    while (yytext[tabAmount] == ' ') {
        tabAmount++;
    }
    tabAmount /= 4;
    indentsTypes[tabAmount] = 'i';
    totalIndent = tabAmount;
}

{FOR} {
    int tabAmount = 0;
    while (yytext[tabAmount] == ' ') {
        tabAmount++;
    }
    tabAmount /= 4;
    indentsTypes[tabAmount] = 'f';
    totalIndent = tabAmount;

    int forAmount = 0;
    for (int i = 0; i < tabAmount + 1; i++) {
        if (indentsTypes[i] == 'f') {
            forAmount++;
        }
    }

    if (forAmount > maxForCount) {
        maxForCount = forAmount;
    }

}

{FUNCTION} {
    int currentReader = 0;
    for (int i = 0; i < yyleng; i++) {
      if (yytext[i] == functionName[currentReader]) {
        currentReader++;
      } else if (yytext[i] != ' ' && yytext[i] != '(') {
        currentReader = 0;
      }
    }
    if (currentReader == strlen(functionName)) {
        functionFound = 1;
    }
}

{BLANC}
.
%%
int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez préciser un nom de fichier !\n");
        return 1;
    }

    if (argc < 3) {
        printf("Veuillez préciser un nom de fonction !\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Le fichier '%s' n'existe pas !\n", argv[1]);
        return 1;
    }

    strcpy(functionName, argv[2]);

    yylex();
    printf("niveau d'imbrication max: %d\n", maxForCount);
    printf("fonction %s: %d\n", functionName, functionFound);
    return 0;
}
