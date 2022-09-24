#ifndef LEXICON_PART_HPP
#define LEXICON_PART_HPP

#include <iostream>
#include "serializable.hpp"

class LexiconPart : public Serializable {

    protected:
        std::string m_lexiconTypeName;

    public:

        LexiconPart(const std::string& lexiconTypeName);

        std::string getLexiconTypeName();

        virtual char getChar() const = 0;
        virtual std::string getString() const = 0;
        virtual void throwError() const = 0;


};

#endif
