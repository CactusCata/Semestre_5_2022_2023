#include "etudiant2.hpp"

Etudiant2(std::string nom, std::string prenom, unsigned int age, unsigned int nb, Matiere *matieres):
Etudiant1(nom, prenom, age, nb)
{
    this->matiere = matiere;
}

Etudiant2(const Etudiant2& student):
Etudiant1(student)
{
    this->matieres = new Matiere[student.getNb()];
    for (unsigned int i = 0; i < student.getNb(); i++) {
        this->matieres[i] = student.matieres[i];
    }
}

~Etudiant2() {
    delete [] this->matieres;
}

void print() {
    Etudiant1::print();
    std::cout << " Matieres: (";
    if (Etudiant1::getNb() > 0) {
      for (unsigned int i = 0; i < Etudiant1::getNb() - 1; i++) {
          this->matieres[i].print();
      }
      this->matieres[Etudiant1::getNb() - 1].print();
    }
    std::cout << ')' << std::endl;
}

double moyenne() {
    unsigned int sum = 0;
    unsigned int sumCoef = 0;

    for (unsigned int i = 0; i < Etudiant1::getNb(); i++) {
        sum += this->matieres[i].getCoef() * Etudiant1::getNotes()[i];
        sumCoef += this->matieres[i].getCoef();
    }

    return static_cast<double>(sum) / sumCoef;
}

Etudiant2 &operator =(const Etudiant2& student) {
    this->Etudiant1::operator=(student);
    for (unsigned int i = 0; i < student.getNb(); i++) {
        this->matieres[i] = student.matieres[i];
    }
    return *this;

}
