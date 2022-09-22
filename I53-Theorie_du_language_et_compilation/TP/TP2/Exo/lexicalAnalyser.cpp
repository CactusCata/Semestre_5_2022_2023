#include "lexicalAnalyser.hpp"

std::vector<LexiconPart *> analex(const std::string text) {
    std::vector<LexiconPart *> lexiconsParts;
    for (unsigned int i = 0; i < text.length();) {
        appendLexicalUnit(lexiconsParts, text, i);

        //if (i + 1 < text.length()) {
        //    anaL.append(",");
        //}
    }

    //anaL.append("]");
    return lexiconsParts;
}

void appendLexicalUnit(std::vector<LexiconPart *> &lexiconsParts, const std::string &text, unsigned int &i) {
    bool foundGroup = false;
    unsigned char c = text[i];

    if (digits.isInCategory(c)) {
        std::string number;
        while (digits.isInCategory(c)) {
            number.push_back(c);

            if (i >= text.length()) {
                break;
            }

            c = text[++i];
        }
        lexiconsParts.push_back(digits.createLexiconPart(number));
    } else {
        for (LexiconType lexical : lexicons) {
            if (lexical.isInCategory(c)) {
                lexiconsParts.push_back(lexical.createLexiconPart(c));
                foundGroup = true;
                break;
            }
        }

        i++;

        if (!foundGroup) {
            throwLexicalAnalyserError(c);
            exit(1);
        }
    }

}

void throwLexicalAnalyserError(const char& orphan) {
    std::cout << "Error while lexical analyse on character : '" << orphan << "' ." << std::endl;
}
