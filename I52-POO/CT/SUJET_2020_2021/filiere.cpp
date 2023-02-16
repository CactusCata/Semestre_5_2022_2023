#include "filiere.hpp"

Filiere::Filiere() {
    this->discipline = "?";
    this->diplome = "?";
    this->niveau = -1;
}

Filiere::Filiere(std::string discipline, std::string diplome, int niveau) {
    this->discipline = discipline;
    this->diplome = diplome;
    this->niveau = niveau;
}

Filiere::Filiere(const Filiere &filiere) {
    this->discipline = filiere.discipline;
    this->diplome = filiere.diplome;
    this->niveau = filiere.niveau;
}

std::string Filiere::Get_discipline() const {
    return this->discipline;
}

std::string Filiere::Get_diplome() const {
    return this->diplome;
}

int Filiere::Get_niveau() const {
    return this->niveau;
}

void Filiere::Put_discipline(std::string discipline) {
    this->discipline = discipline;
}

void Filiere::Put_diplome(std::string diplome) {
    this->diplome = diplome;
}

void Filiere::Put_niveau(int niveau) {
    this->niveau = niveau;
}
