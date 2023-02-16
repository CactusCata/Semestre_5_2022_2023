#include "asa_utils.h"

void yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  exit(0);
}