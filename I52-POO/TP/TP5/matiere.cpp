#include "matiere.hpp"

Matiere::Matiere(std::string nom) {
  this->nom = nom;
}

Matiere::Matiere(const Matiere &matiere):
Matiere(matiere.nom)
{

}

Matiere::Matiere():
Matiere("?")
{

}

Matiere::~Matiere() {

}

Matiere &Matiere::operator =(const Matiere & matiere) {
  this->nom = matiere.nom;
  return *this;
}
