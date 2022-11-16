#include "personne.hpp"

Personne::Personne(std::string nom, std::string prenom, unsigned int age) {
  this->nom = nom;
  this->prenom = prenom;
  this->age = age;
}

Personne::Personne(const Personne &p):
Personne(p.nom, p.prenom, p.age)
{

}

Personne::Personne():
Personne("?", "?", 0)
{

}

Personne::~Personne() {

}

Personne &Personne::operator =(const Personne &p) {
  this->nom = p.nom;
  this->prenom = p.prenom;
  this->age = p.age;
  return *this;
}

std::ostream &operator <<(std::ostream &stream, const Personne& personne) {
  return stream << personne.nom << " " << personne.prenom << " " << personne.age << ".";
}
