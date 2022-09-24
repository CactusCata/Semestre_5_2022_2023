#ifndef LEXICON_TYPE_ENUM_HPP
#define LEXICON_TYPE_ENUM_HPP

#include "lexiconType.hpp"


const std::string LEXICON_DIGIT_TYPE = "NBR";
const LexiconType digits({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, LEXICON_DIGIT_TYPE);

const std::string LEXICON_OPERATOR_ADD_SUB_TYPE = "OP_ADD_SUB";
const LexiconType operatorsAddSub({'+', '-'}, LEXICON_OPERATOR_ADD_SUB_TYPE);

const std::string LEXICON_OPERATOR_MULT_DIV_TYPE = "OP_MULT_DIV";
const LexiconType operatorsMultDiv({'*', '/'}, LEXICON_OPERATOR_MULT_DIV_TYPE);

const std::string LEXICON_BRACKET_LEFT_TYPE = "BRACKET_L";
const LexiconType bracketLeft({'('}, LEXICON_BRACKET_LEFT_TYPE);

const std::string LEXICON_BRACKET_RIGHT_TYPE = "BRACKET_R";
const LexiconType bracketRight({')'}, LEXICON_BRACKET_LEFT_TYPE);

// use empty space bar character because he is removed before all (check main.cpp)
const std::string LEXICON_OUT_OF_BOUNDS = "OUT_OF_BOUNDS";
const LexiconType bracketOutOfBounds({' '}, LEXICON_OUT_OF_BOUNDS);

const std::initializer_list<LexiconType> lexicons = {digits, operatorsAddSub, operatorsMultDiv, bracketLeft, bracketRight};


#endif
