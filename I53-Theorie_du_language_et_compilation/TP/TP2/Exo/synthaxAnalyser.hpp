#ifndef SYNTHAX_ANALYSER_HPP
#define SYNTHAX_ANALYSER_HPP

#include <iostream>
#include "stack.hpp"
#include "lexiconPartEnum.hpp"

void axiom();
void E_1();
void E_2();
void T_1();
void T_2();
void P();
void NB();

void isCorrect(char *cc);

void throwSyntaxError();


#endif
