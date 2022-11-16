#include "matiere.hpp"

Matiere::Matiere():
Matiere("Default", 0)
{

}

Matiere::Matiere(std::string nom, unsigned int coef) {
    this->nom = nom;
    this->coef = coef;
}

void Matiere::print() {
    std::cout << this->getNom() << '(' << this->getCoef() << ')' << std::endl;
}

std::string Matiere::getNom() {
    return this->nom;
}

unsigned int Matiere::getCoef() {
    return this->coef;
}
