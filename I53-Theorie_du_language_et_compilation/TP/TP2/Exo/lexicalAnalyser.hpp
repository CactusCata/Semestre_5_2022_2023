#ifndef LEXICAL_ANALYSER_HPP
#define LEXICAL_ANALYSER_HPP

#include <iostream>
#include "lexiconPart.hpp"

std::string analex(const char *expr, const unsigned int& size);

void throwLexicalAnalyserError(const char& orphan);

#endif