#include "synthaxAnalyser.hpp"

char *cc;
int ccPoint = 0;

bool findError = false;
int ccPointError = -1;

void EXP_1() {
    NB();
    EXP_2();
}

void EXP_2() {
    //std::cout << "[E2] Recherche de + ou - " << std::endl;
    char op = cc[ccPoint];
    if (op == '+' || op == '-') {
        //std::cout << "[E2] + ou - trouvé: " << std::endl;
        ccPoint++;
        NB();
        EXP_2();
        std::cout << op;
    }
}

void NB() {
    //std::cout << "[E2] Recherche d'un nombre: " << ccPoint << std::endl;
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    bool finded = false;
    for (unsigned int i = 0; i < 10 && !finded; i++) {
        //std::cout << cc[ccPoint] << " : " << digits[i] << std::endl;
        if (cc[ccPoint] == digits[i]) {
            //std::cout << "[NB] Le nombre " << digits[i] << " a été trouvé." << std::endl;
            finded = true;
            std::cout << cc[ccPoint];
            ccPoint++;
        }
    }

    if (!finded) {
        if (!findError) {
            findError = true;
            ccPointError = ccPoint;
        }
        //std::cout << "[NB] N'a pas trouve de nombre: " << ccPoint << std::endl;
    }
}

void isCorrect(char *cc1) {
    cc = cc1;
    EXP_1();
    if (findError) {
        std::cout << "Une erreur a ete trouvee a la lecture du caractere " << cc[ccPointError] << " (col " << ccPointError << ")" << std::endl;
    } else if (cc[ccPoint] != '\0') {
        std::cout << "Une erreur a ete trouvee a la lecture du caractere " << cc[ccPoint] << " (col " << ccPoint << ")" << std::endl;
    } else {
        std::cout << "Expression correcte" << std::endl;
    }
}