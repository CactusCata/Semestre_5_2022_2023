#ifndef LEXICAL_ANALYSER_HPP
#define LEXICAL_ANALYSER_HPP

#include <iostream>
#include "lexiconTypeEnum.hpp"
#include "lexiconPart.hpp"

std::vector<LexiconPart *> analex(const std::string text);

void throwLexicalAnalyserError(const char& orphan);

void appendLexicalUnit(std::vector<LexiconPart *> &lexiconsParts, const std::string &text, unsigned int &i);

#endif
