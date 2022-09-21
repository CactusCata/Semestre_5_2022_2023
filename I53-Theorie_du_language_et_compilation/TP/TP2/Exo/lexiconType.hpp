#ifndef LEXICON_TYPE_HPP
#define LEXICON_TYPE_HPP

#include <iostream>
#include <vector>

#include "lexiconPart.hpp"

class LexiconType {

    protected:
        std::vector<char> m_symbols;
        std::string m_name;

    public:
        LexiconType(const std::vector<char>& symbols, const std::string& name);

        LexiconPart serialize(const char& symbol) const;
        bool isInCategory(const char& symbol) const;

};

#endif
