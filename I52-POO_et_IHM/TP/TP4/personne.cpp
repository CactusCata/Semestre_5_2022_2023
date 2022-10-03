#include "personne.hpp"

Personne::Personne(std::string nom, std::string prenom, unsigned int age) {
    this->m_nom = nom;
    this->m_prenom = prenom;
    this->m_age = age;
}

void Personne::print() const {
    std::cout << this->m_nom << " " << this->m_prenom << " " << this->m_age << " ans. " << std::endl;
}

void Personne::ageing() {
    this->m_age++;
}
