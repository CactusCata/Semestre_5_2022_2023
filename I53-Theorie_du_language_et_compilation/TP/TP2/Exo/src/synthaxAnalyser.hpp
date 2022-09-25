#ifndef SYNTHAX_ANALYSER_HPP
#define SYNTHAX_ANALYSER_HPP

#include <iostream>
#include <vector>

#include "stack.hpp"
#include "queue.hpp"
#include "lexiconTypeEnum.hpp"
#include "lexiconPart.hpp"

void axiom();
void E_1();
void E_2();
void T_1();
void T_2();
void P();
void NB();

Queue analSynthax(const std::vector<LexiconPart *> &lexiconsParts);

void throwSyntaxError();

LexiconPart *getLexiconPart();


#endif
