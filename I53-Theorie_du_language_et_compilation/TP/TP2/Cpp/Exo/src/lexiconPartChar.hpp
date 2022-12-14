#ifndef LEXICON_PART_CHAR_HPP
#define LEXICON_PART_CHAR_HPP

#include "lexiconPart.hpp"

class LexiconPartChar : public LexiconPart {

    private:

        char m_value;

    public:

        LexiconPartChar(const std::string& lexiconTypeName, const char& value);

        virtual std::string serialize();

        virtual char getChar() const;
        virtual std::string getString() const;
        virtual void throwError() const;

};

#endif