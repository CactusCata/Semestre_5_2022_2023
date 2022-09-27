#include "etudiant1.hpp"

Etudiant1::Etudiant1(std::string nom, std::string prenom, unsigned int age, unsigned int nb):
Personne(nom, prenom, age)
{
    this->nb = nb;
    this->notes = new unsigned int[nb];
    for (unsigned int i = 0; i < nb; i++) {
      this->notes[i] = 0;
    }
}

Etudiant1::Etudiant1(const Etudiant1& student):
Personne(student)
{
  this->nb = student.nb;
  this->notes = new unsigned int[student.nb];
  for (unsigned int i = 0; i < this->nb; i++) {
    this->notes[i] = student.notes[i];
  }
}

Etudiant1::~Etudiant1() {
    delete [] this->notes;
}

void Etudiant1::ajouterNotes(unsigned int* notes) {
    for (unsigned int i = 0; i < this->nb; i++) {
        this->notes[i] = notes[i];
    }
}

void Etudiant1::print() {
    Personne::print();
    std::cout << " | notes: (";
    if (this->nb > 0) {
        for (unsigned int i = 0; i < this->nb; i++) {
            std::cout << this->notes[i] << "/20, ";
        }
        std::cout << this->notes[this->nb - 1] << "/20";
     }
    std::cout << ')' << std::endl;
}

double Etudiant1::moyenne() {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < this->nb; i++) {
        sum += this->notes[i];
    }
    return static_cast<double>(sum) / this->nb;
}

Etudiant1& Etudiant1::operator =(const Etudiant1& student) {
    if (this->nb == student.nb) {
        for (unsigned int i = 0; i < this->nb; i++) {
            this->notes[i] = student.notes[i];
        }
    }
    return *this;
}
