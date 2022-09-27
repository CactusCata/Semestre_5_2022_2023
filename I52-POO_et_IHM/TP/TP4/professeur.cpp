#include "professeur.hpp"

Professor::Professor(std::string nom, std::string prenom, unsigned int age, std::string statut):
Personne(nom, prenom, age)
{
    this->statut = statut;
    this->heures = 0;
}

void Professor::print() {
    Personne::print();
    std::cout << " | statut: " << this->statut << " | heures: " << this->heures << std::endl;
}

void Professor::work(unsigned int hourCount) {
    this->heures += hourCount;
}
