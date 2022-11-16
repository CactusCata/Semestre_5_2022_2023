%{
  #include <stdio.h>
  #include <ctype.h>
  #include <stdlib.h>

  int yylval;
  int yylex();
  int yyerror(char *msg);

  int myexp(int x, int n);

  int memoryArray[26];
%}


%token NB PLUS MOINS MULT DIV POWER FIN TO_REMOVE PAR_L PAR_R MEM AFFECT
// Plus on descend, plus c'est prioritaire
%left PLUS MOINS
%left MULT DIV
%right POWER
%right AFFECT

%start PROG

%%

PROG : PROG EXP FIN {printf("%d\n", $2);}
| PROG MEM_AFFECT FIN {printf("Affectation de la valeur %d.\n", $2);}
|
;

EXP : EXP PLUS EXP {$$ = $1 + $3;}
| EXP MOINS EXP {$$ = $1 - $3;}
| EXP MULT EXP {$$ = $1 * $3;}
| EXP DIV EXP {$$ = $1 / $3;}
| EXP POWER EXP {$$ = myexp($1, $3);}
| PAR_L EXP PAR_R {$$ = $2;}
| NB {$$ = $1;}
| MEM {$$ = memoryArray['A' - $1];};

MEM_AFFECT : MEM AFFECT EXP {
  memoryArray['A' - $1] = $3;
  $$ = $3;
};


%%

int main(int argc, char *argv[]) {
  for (int i = 0; i < 26; i++) {
    memoryArray[i] = 0;
  }
  yyparse();
  return 0;
}

int yylex() {
  int car;
  while ((car = getchar()) == ' ');

  if (car == EOF) {
    return 0;
  }

  if (isdigit(car)) {
    int res = 0;
    while (isdigit(car)) {
      res *= 10;
      res += car - '0';
      car = getchar();
    }
    yylval = res;
    ungetc(car, stdin); // permet de remttre dans le flux un character
    return NB;
  }

  if (car == '*') {
    car = getchar();
    if (car == '*') {
      return POWER;
    } else {
      ungetc(car, stdin);
      return MULT;
    }
  }

  if ('A' <= car && car <= 'Z') {
    yylval = car;
    return MEM;
  }

  switch (car) {
    case '+': return PLUS;
    case '-': return MOINS;
    case '*': return MULT;
    case '/': return DIV;
    case '(' : return PAR_L;
    case ')' : return PAR_R;
    case '=' : return AFFECT;
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
