#include "synthaxAnalyser.hpp"

char *cc;
int ccPoint = 0;

Stack instructionsStack;

void E_1() {
    T_1();
    E_2();
}

void E_2() {
    char op = cc[ccPoint];
    if (op == '+' || op == '-') {
        ccPoint++;
        T_1();
        E_2();
        instructionsStack.push(op);
    }
}

void T_1() {
    P();
    T_2();
}

void T_2() {
    char op = cc[ccPoint];
    if (op == '*' || op == '/') {
        ccPoint++;
        P();
        T_2();
        instructionsStack.push(op);
    }
}

void P() {
    if (cc[ccPoint] == '(') {
        instructionsStack.push('(');
        ccPoint++;
        E_1();
        if (cc[ccPoint] != ')') {
            throwSyntaxError();
        }
        instructionsStack.push(')');
        ccPoint++;
    } else {
        NB();
    }


}

void NB() {
    //std::cout << "[E2] Recherche d'un nombre: " << ccPoint << std::endl;
    
    if (digits.isInCategory(cc[ccPoint])) {
        instructionsStack.push(cc[ccPoint]);
        ccPoint++;
    } else {
        throwSyntaxError();
    }
    
}

void isCorrect(char *cc1) {
    cc = cc1;
    E_1();
    if (cc[ccPoint] != '\0') {
        std::cout << "Une erreur a ete trouvee a la lecture du caractere " << cc[ccPoint] << " (col " << ccPoint << ")" << std::endl;
    } else {
        std::cout << "Expression correcte" << std::endl;
        instructionsStack.print();
    }
}

void throwSyntaxError() {
    std::cout << "Une erreur a ete trouvee a la lecture du caractere " << cc[ccPoint] << " (col " << ccPoint << ")" << std::endl;
    exit(0);
}