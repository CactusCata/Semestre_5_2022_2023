#include "etudiant.hpp"

Etudiant::Etudiant(std::string nom, std::string prenom, unsigned int age, Cursus cursus):
Personne(nom, prenom, age)
{
  this->cursus = cursus;
}

Etudiant::Etudiant():
Personne()
{
  Cursus c;
  this->cursus = c;
}

Etudiant::Etudiant(const Etudiant &etudiant):
Personne(*this)
{
  this->cursus = etudiant.cursus;
}

Etudiant::~Etudiant() {

}

Etudiant &Etudiant::operator =(const Etudiant &etudiant) {
  if (this != &etudiant) {
    this->Personne::operator=(etudiant);
    this->cursus = etudiant.cursus;
  }
  return *this;
}
