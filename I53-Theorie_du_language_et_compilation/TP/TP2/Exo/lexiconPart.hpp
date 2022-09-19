#ifndef LEXICON_PART_HPP
#define LEXICON_PART_HPP

#include <iostream>
#include <vector>

class LexiconPart {

    private:
        std::vector<char> m_symbols;
        std::string m_name;

    public:
        LexiconPart(const std::vector<char>& symbols, const std::string& name);

        std::string serialize(const char& symbol);
        bool isInCategory(const char& symbol);

};

const LexiconPart digits({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, "NBR");
const LexiconPart operators({'+', '-', '*', '/'}, "OP");
const LexiconPart bracketLeft({'('}, "BRACKETL");
const LexiconPart bracketRight({')'}, "BRACKETR");

const std::initializer_list<LexiconPart> lexicons = {digits, operators, bracketLeft, bracketRight}; 

#endif