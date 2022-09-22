#ifndef LEXICON_TYPE_ENUM_HPP
#define LEXICON_TYPE_ENUM_HPP

#include "lexiconType.hpp"

const LexiconType digits({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, "NBR");
const LexiconType operators({'+', '-', '*', '/'}, "OP");
const LexiconType bracketLeft({'('}, "BRACKETL");
const LexiconType bracketRight({')'}, "BRACKETR");

const std::initializer_list<LexiconType> lexicons = {digits, operators, bracketLeft, bracketRight};


#endif
