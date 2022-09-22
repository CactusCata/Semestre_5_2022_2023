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