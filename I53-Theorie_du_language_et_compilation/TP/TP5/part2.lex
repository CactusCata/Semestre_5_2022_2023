%{
    /* Prologue */
    #include <stdio.h>
    #include <string.h>

    typedef struct list_symb {
        char symb[256];
        int count;
        struct list_symb *suiv;
    } list_symb;

    list_symb histogram;

    int inserer(char *nom, list_symb *ptr);
    void print_list(list_symb *ptr);
    void freeList(list_symb *ptr);

%}
%option nounput
%option noinput
/* Definitions */
BLANC [ \t\n]
LETTRE [a-zA-Z]
MOT {LETTRE}+
%%
{MOT} {
    inserer(yytext, &histogram);
}

{BLANC}

. // dans tous les autres cas, on fait rien
%%
int inserer(char *nom, list_symb *ptr) {
    while (ptr->suiv != NULL && (strcmp(nom, ptr->symb) != 0)) {
        ptr = ptr->suiv;
    }

    if (strcmp(nom, ptr->symb) == 0) {
        ptr->count++;
        return 0;
    } else {
        ptr->suiv = (list_symb *) malloc(sizeof(list_symb));
        strcpy(ptr->suiv->symb, nom);
        ptr->suiv->count = 1;
        ptr->suiv->suiv = NULL;
        return 1;
    }
}

void print_list(list_symb *ptr) {
    while (ptr != NULL) {
        printf("mot \"%s\" : %d\n", ptr->symb, ptr->count);
        ptr = ptr->suiv;
    }
}

void freeList(list_symb *ptr) {
    if (ptr != NULL) {
        freeList(ptr->suiv);
        free(ptr);
    }
}

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
    histogram.symb[0] = '\0';
    histogram.count = 0;
    histogram.suiv = NULL;

    yylex();
    print_list(&histogram);
    freeList(histogram.suiv);
    fclose(yyin);
    yylex_destroy();
    return 0;
}
