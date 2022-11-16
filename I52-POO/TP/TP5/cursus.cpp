#include "cursus.hpp"

Cursus::Cursus(std::string intitule, const Professeur &responsable, Matiere *liste_matieres, unsigned int liste_matieres_size) {
  this->intitule = intitule;
  this->responsable = responsable;
  this->liste_matieres_size = liste_matieres_size;
  this->liste_matieres = new Matiere[liste_matieres_size];
  for (unsigned int i = 0; i < liste_matieres_size; i++) {
    this->liste_matieres[i] = liste_matieres[i];
  }
}

Cursus::Cursus() {
  this->intitule = "?";
  Professeur p;
  this->responsable = p;
  this->liste_matieres_size = 0;
  this->liste_matieres = NULL;
}

Cursus::Cursus(const Cursus &cursus):
Cursus(cursus.intitule, cursus.responsable, cursus.liste_matieres, cursus.liste_matieres_size)
{

}

Cursus::~Cursus() {
  delete [] this->liste_matieres;
}

Cursus &Cursus::operator =(const Cursus &cursus) {

  if (&cursus != this) {
    this->intitule = intitule;
    this->responsable = responsable;

    if (this->liste_matieres_size != cursus.liste_matieres_size) {
      if (this->liste_matieres != NULL) {
        delete [] this->liste_matieres;
      }
      this->liste_matieres = new Matiere[cursus.liste_matieres_size];
    }

    this->liste_matieres_size = liste_matieres_size;
    for (unsigned int i = 0; i < this->liste_matieres_size; i++) {
      this->liste_matieres[i] = cursus.liste_matieres[i];
    }

  }

  return *this;

}
