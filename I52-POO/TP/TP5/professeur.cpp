#include "professeur.hpp"

Professeur::Professeur(std::string nom, std::string prenom, unsigned int age, Matiere *liste_enseignements, unsigned int liste_enseignements_size):
Personne(nom, prenom, age)
{

  this->liste_enseignements_size = liste_enseignements_size;
  this->liste_enseignements = new Matiere[this->liste_enseignements_size];
  for (unsigned int i = 0; i < liste_enseignements_size; i++) {
    this->liste_enseignements[i] = liste_enseignements[i];
  }

}

Professeur::Professeur():
Personne()
{
  this->liste_enseignements_size = 0;
  this->liste_enseignements = NULL;
}

Professeur::Professeur(const Professeur &professeur):
Personne(*this)
{
  this->liste_enseignements_size = professeur.liste_enseignements_size;
  this->liste_enseignements = new Matiere[this->liste_enseignements_size];
  for (unsigned int i = 0; i < liste_enseignements_size; i++) {
    this->liste_enseignements[i] = professeur.liste_enseignements[i];
  }
}

Professeur::~Professeur() {
  delete [] this->liste_enseignements;
}

Professeur &Professeur::operator =(const Professeur &professeur) {

  if (&professeur != this) {
    this->Personne::operator=(professeur);

    if (this->liste_enseignements_size != professeur.liste_enseignements_size) {
      if (this->liste_enseignements != NULL) {
        delete [] this->liste_enseignements;
      }
      this->liste_enseignements = new Matiere[professeur.liste_enseignements_size];
    }

    this->liste_enseignements_size = professeur.liste_enseignements_size;
    for (unsigned int i = 0; i < this->liste_enseignements_size; i++) {
      this->liste_enseignements[i] = professeur.liste_enseignements[i];
    }
  }

  return *this;

}
