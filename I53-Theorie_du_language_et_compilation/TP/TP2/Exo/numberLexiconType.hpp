#ifndef NUMBER_LEXICON_TYPE_HPP
#define NUMBER_LEXICON_TYPE_HPP

#include "lexiconPart.hpp"
#include "lexiconType.hpp"
#include <iostream>

class NumberLexiconType: public LexiconType {

    public:

        NumberLexiconType(const std::vector<char>& symbols, const std::string& name);

        LexiconPart serialize(const std::string& text) const;

};

#endif
