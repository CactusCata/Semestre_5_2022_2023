#include "lexiconPart.hpp"

LexiconPart::LexiconPart(const std::string& lexiconTypeName) {
    this->m_lexiconTypeName = lexiconTypeName;
}

std::string LexiconPart::getLexiconTypeName() {
    return this->m_lexiconTypeName;
}