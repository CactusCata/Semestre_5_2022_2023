#include "lexiconPart.hpp"

LexiconPart::LexiconPart(const std::vector<char>& symbolss, const std::string& name):
m_symbols(std::move(symbolss)),
m_name(std::move(name))
{
}

std::string LexiconPart::serialize(const char& symbol) {
    std::string serialized;
    serialized.append("('");
    serialized.append(m_name);
    serialized.append("',");
    serialized.push_back(symbol);
    serialized.append(")");
    return serialized;
}

bool LexiconPart::isInCategory(const char& symbol) {
    for (const char &c : this->m_symbols) {
        std::cout << c << " " << symbol << std::endl;
        if (c == symbol) {
            std::cout << "founded" << std::endl;
            return true;
        }
    }
    return false;
}