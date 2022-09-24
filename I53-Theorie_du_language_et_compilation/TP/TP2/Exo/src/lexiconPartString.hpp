#ifndef LEXICON_PART_STRING_HPP
#define LEXICON_PART_STRING_HPP

#include "lexiconPart.hpp"

#include <iostream>

class LexiconPartString : public LexiconPart {

    private:

        std::string m_value;

    public:

        LexiconPartString(const std::string& lexiconTypeName, const std::string& value);

        virtual std::string serialize();

        virtual std::string getString() const;
        virtual char getChar() const;
        virtual void throwError() const;

};

#endif