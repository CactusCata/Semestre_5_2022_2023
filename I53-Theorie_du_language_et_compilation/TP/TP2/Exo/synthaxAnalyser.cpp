#include "synthaxAnalyser.hpp"

std::vector<LexiconPart *> lexiconsParts;
size_t lexiconIndex = 0;

Stack instructionsStack;

void E_1() {
    T_1();
    E_2();
}

void E_2() {
    LexiconPart *lp = getLexiconPart();
    if (lp->getLexiconTypeName() == LEXICON_OPERATOR_ADD_SUB_TYPE) {
        lexiconIndex++;
        T_1();
        E_2();
        instructionsStack.push(lp);
    }
}

void T_1() {
    P();
    T_2();
}

void T_2() {
    LexiconPart *lp = getLexiconPart();
    if (lp->getLexiconTypeName() == LEXICON_OPERATOR_MULT_DIV_TYPE) {
        lexiconIndex++;
        P();
        T_2();
        instructionsStack.push(lp);
    }
}

void P() {
    LexiconPart *lp = getLexiconPart();
    if (lp->getLexiconTypeName() == LEXICON_BRACKET_LEFT_TYPE) {
        instructionsStack.push(lp);
        lexiconIndex++;
        E_1();
        if (lp->getLexiconTypeName() != LEXICON_BRACKET_RIGHT_TYPE) {
            throwSyntaxError();
        }
        instructionsStack.push(lp);
        lexiconIndex++;
    } else {
        NB();
    }


}

void NB() {
    
    LexiconPart *lp = getLexiconPart();
    if (lp->getLexiconTypeName() == LEXICON_DIGIT_TYPE) {
        lexiconIndex++;
        instructionsStack.push(lp);
    } else {
        throwSyntaxError();
    }
    
}

void isCorrect(const std::vector<LexiconPart *> &lp) {
    lexiconsParts = lp;
    E_1();
    if (lexiconsParts.size() != lexiconIndex) {
        std::cout << "Une erreur a ete trouvee a la lecture du caractere " << lexiconsParts.at(lexiconIndex)->getChar() << " (col " << lexiconIndex << ")" << std::endl;
    } else {
        std::cout << "Expression correcte" << std::endl;
        instructionsStack.print();
    }
}

void throwSyntaxError() {
    if (lexiconIndex >= lexiconsParts.size()) {
        std::cout << "Des caracteres etaient encore attendus a la fin de la chaine." << std::endl;
    } else {
        lexiconsParts.at(lexiconIndex)->throwError();
    }
    exit(0);
}

LexiconPart *getLexiconPart() {
    if (lexiconIndex < lexiconsParts.size()) {
        return lexiconsParts[lexiconIndex];
    } else {
        return bracketOutOfBounds.createLexiconPart(" ");
    }
}