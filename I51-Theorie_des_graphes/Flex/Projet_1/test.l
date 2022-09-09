/* Definitions */
/*
%{
    
}%
*/

/*  Rules */
%%

[a-z]{4} {printf("Single lower case character\n");}
. {printf("Autre\n");}
\n {printf("Saut de ligne\n");}

%%

int yywrap() {return 0;}

int main() {
    printf("Enter string: ");
    yylex();

    return 0;
}
