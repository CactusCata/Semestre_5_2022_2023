#include "synthaxAnalyser.hpp"

std::vector<LexiconPart *> lexiconsParts;
size_t lexiconIndex = 0;

Queue instructionsStack;

void E_1() {
    T_1();
    E_2();
}

void E_2() {
    // Addition ou soustraction
    LexiconPart *lp = getLexiconPart();
    if (lp->getLexiconTypeName() == LEXICON_OPERATOR_ADD_SUB_TYPE) {
        lexiconIndex++;
        T_1();
        E_2();
        instructionsStack.add(lp);
    }
}

void T_1() {
    P();
    T_2();
}

void T_2() {
    // Multiplication ou division
    LexiconPart *lp = getLexiconPart();
    if (lp->getLexiconTypeName() == LEXICON_OPERATOR_MULT_DIV_TYPE) {
        lexiconIndex++;
        P();
        T_2();
        instructionsStack.add(lp);
    }
}

void P() {
    // Parentheses
    LexiconPart *lp = getLexiconPart();
    if (lp->getLexiconTypeName() == LEXICON_BRACKET_LEFT_TYPE) {
        //instructionsStack.push(lp);
        lexiconIndex++;
        E_1();
        LexiconPart *newLp = getLexiconPart();
        if (newLp->getLexiconTypeName() != LEXICON_BRACKET_RIGHT_TYPE) {
            throwSyntaxError();
        }
        //instructionsStack.push(newLp);
        lexiconIndex++;
    } else {
        NB();
    }


}

void NB() {
    
    LexiconPart *lp = getLexiconPart();
    if (lp->getLexiconTypeName() == LEXICON_DIGIT_TYPE) {
        lexiconIndex++;
        instructionsStack.add(lp);
    } else {
        throwSyntaxError();
    }
    
}

Queue analSynthax(const std::vector<LexiconPart *> &lp) {
    lexiconsParts = lp;
    E_1();
    if (lexiconsParts.size() != lexiconIndex) {
        std::cout << "Une erreur a ete trouvee a la lecture du caractere " << lexiconsParts.at(lexiconIndex)->getChar() << " (col " << lexiconIndex << ")" << std::endl;
        exit(1);
    } else {
        std::cout << "Expression correcte" << std::endl;
        instructionsStack.print();
        return instructionsStack;
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