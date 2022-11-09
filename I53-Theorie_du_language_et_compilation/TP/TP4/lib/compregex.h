#ifndef COMPREGEX_H
#define COMPREGEX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "afn.h"

void E1();

void E2();

void C1();

void C2();

void K();

void B();

void R();

void P();

void letter();

void buildStackText(char *text);

char getCurrentCharacter();

void throwSyntaxError(char *text);

void addToTextStack(char c);

AFN buildAFNFromRE(char *re);

#endif