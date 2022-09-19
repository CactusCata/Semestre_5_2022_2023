#include "lexicalAnalyser.hpp"

std::string analex(const char *expr, const unsigned int& size) {
    std::string anaL("[");
    for (unsigned int i = 0; i < size - 1; i++) {
        const char c = expr[i];
        bool foundGroup = false;
        for (LexiconPart lexical : lexicons) {
            if (lexical.isInCategory(c)) {
                anaL.append(lexical.serialize(c));
                foundGroup = true;
                break;
            }
        }
        anaL.append(",");

        if (!foundGroup) {
            throwLexicalAnalyserError(c);
            exit(1);
        }
    }
    anaL.append("]");
    return anaL;
}

void throwLexicalAnalyserError(const char& orphan) {
    std::cout << "Error while lexical analyse on character : '" << orphan << "' ." << std::endl;
}