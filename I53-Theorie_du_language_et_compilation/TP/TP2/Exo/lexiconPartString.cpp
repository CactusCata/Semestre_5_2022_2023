#include "lexiconPartString.hpp"

LexiconPartString::LexiconPartString(const std::string& lexiconTypeName, const std::string& value):
LexiconPart(lexiconTypeName)
{
    this->m_value = value;
}

std::string LexiconPartString::serialize() {
    std::string serialized;
    serialized.append("('");
    serialized.append(this->m_lexiconTypeName);
    serialized.append("',");
    serialized.append(this->m_value);
    serialized.append(")");
    return serialized;
}

std::string LexiconPartString::getString() const {
    return this->m_value;
}

char LexiconPartString::getChar() const {
    return '?';
}

void LexiconPartString::throwError() const {
    std::cout << "Error lors de la chaine de caractere '" << this->getString() << "'."; 
}