#ifndef LEXICON_TYPE_HPP
#define LEXICON_TYPE_HPP

#include <iostream>
#include <vector>

#include "lexiconPart.hpp"
#include "lexiconPartChar.hpp"
#include "lexiconPartString.hpp"

class LexiconType {

    protected:
        std::vector<char> m_symbols;
        std::string m_name;

    public:
        LexiconType(const std::vector<char>& symbols, const std::string& name);

        LexiconPartChar* createLexiconPart(const char& symbol) const;
        LexiconPartString* createLexiconPart(const std::string& text) const;
        bool isInCategory(const char& symbol) const;

};

#endif
