#ifndef LEXICON_PART_HPP
#define LEXICON_PART_HPP

#include <iostream>

class LexiconPart {

    protected:
        std::string m_lexiconTypeName;

    public:

        LexiconPart(const std::string& lexiconTypeName);

        virtual std::string serialize() = 0;

};

#endif
