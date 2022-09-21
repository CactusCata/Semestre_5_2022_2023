#include "numberLexiconType.hpp"

NumberLexiconPart::NumberLexiconType(const std::vector<char>& symbols, const std::string& name):
LexiconType(symbols, name)
{

}

LexiconPart NumberLexiconType::serialize(const std::string& text) const {

    std::string serialized;
    serialized.append("('");
    serialized.append(m_name);
    serialized.append("',");
    serialized.append(text);
    serialized.append(")");
    return serialized;

}
