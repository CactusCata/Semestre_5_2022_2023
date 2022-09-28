#include "lexiconType.hpp"

LexiconType::LexiconType(const std::vector<char>& symbols, const std::string& name):
m_symbols(std::move(symbols)),
m_name(std::move(name))
{
}

LexiconPartChar* LexiconType::createLexiconPart(const char& symbol) const {
    LexiconPartChar *lexicon = new LexiconPartChar(this->m_name, symbol);
    return lexicon;
}

LexiconPartString* LexiconType::createLexiconPart(const std::string& text) const {
    LexiconPartString *lexicon = new LexiconPartString(this->m_name, text);
    return lexicon;
}

bool LexiconType::isInCategory(const char& symbol) const {
    for (const char &c : this->m_symbols) {
        if (c == symbol) {
            return true;
        }
    }
    return false;
}
