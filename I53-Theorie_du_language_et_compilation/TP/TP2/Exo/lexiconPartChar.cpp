#include "lexiconPartChar.hpp"

LexiconPartChar::LexiconPartChar(const std::string& lexiconTypeName, const char& value):
LexiconPart(lexiconTypeName)
{
    this->m_value = value; 
}

std::string LexiconPartChar::serialize() {
    std::string serialized;
    serialized.append("('");
    serialized.append(this->m_lexiconTypeName);
    serialized.append("',");
    serialized.push_back(this->m_value);
    serialized.append(")");
    return serialized;
}