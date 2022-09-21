#ifndef LEXICAL_ANALYSER_HPP
#define LEXICAL_ANALYSER_HPP

#include <iostream>
#include "lexiconTypeEnum.hpp"
#include "lexiconPart.hpp"

std::string analex(const std::string text);

void throwLexicalAnalyserError(const char& orphan);

void appendLexicalUnit(std::string &lexicalsUnits, const std::string &text, unsigned int &i);

#endif
