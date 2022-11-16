%{
  #include <stdio.h>
  #include <ctype.h>
  #include <stdlib.h>
  
  int yylval;
  int yylex();
  int yyerror(char *msg);
  
  int myexp(int x, int n);

%}


%token NB PLUS MOINS MULT DIV FIN TO_REMOVE
%left PLUS

%start PROG

%%

PROG : EXP FIN {
  printf("%d\n", $1 );
  return 1;
}

EXP : MULT_DIV {
  $$ = $1;
} 
| EXP PLUS MULT_DIV {
  $$ = $1 + $3;
}
| EXP MOINS MULT_DIV {
  $$ = $1 - $3;
};

MULT_DIV : MULT_DIV MULT POWER {$$ = $1 * $3;} | MULT_DIV DIV POWER {$$ = $1 / $3;}| POWER {$$ = $1;};

POWER : POWER MULT MULT ESP1 {$$ = myexp($1, $4);}| ESP1 {$$ = $1;};

ESP1 : TO_REMOVE ESP1 {$$ = $2;} | ESP2 {$$ = $1;};

ESP2 : ESP2 TO_REMOVE {$$ = $1;} | NB {$$ = $1;}
;
%%

int main(int argc, char *argv[]) {
  yyparse();
  return 0;
}

int yylex() {
  int car = getchar();

  if (car == EOF) {
    return 0;
  }

  if (isdigit(car)) {
    yylval = car - '0';
    return NB;
  }

  switch (car) {
    case '+': return PLUS;
    case '-': return MOINS;
    case '*': return MULT;
    case '/': return DIV;
    case '\n': return FIN;
    case ' ': return TO_REMOVE;
    case '\t': return TO_REMOVE;
  }
  return -1;
}
 
int yyerror(char *msg) {
  printf("\n%s\n", msg);
  return 1;
}

int myexp(int x, int n) {
  int res = 1;
  while (n) {
    if (n & 1) {
      res *= x;
    }
    x *= x;
    n >>= 1;
  }
  return res;
}
