#ifndef LEXICON_TYPE_ENUM_HPP
#define LEXICON_TYPE_ENUM_HPP

#include "lexiconType.hpp"
#include "numberLexiconType.hpp"

const NumberLexiconPart digits({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, "NBR");
const LexiconPart operators({'+', '-', '*', '/'}, "OP");
const LexiconPart bracketLeft({'('}, "BRACKETL");
const LexiconPart bracketRight({')'}, "BRACKETR");

const std::initializer_list<LexiconPart> lexicons = {digits, operators, bracketLeft, bracketRight};


#endif
