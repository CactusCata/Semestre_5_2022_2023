#include "etudiant2.hpp"

Etudiant2(std::string nom, std::string prenom, unsigned int age, unsigned int nb, Matiere *matieres):
Etudiant1(nom, prenom, age, nb)
{
    this->matiere = matiere;
}

Etudiant2(const Etudiant2& student):
Etudiant1(student)
{
    
}

~Etudiant2() {

}

void print() {

}

double moyenne() {

}

Etudiant2 &operator =(const Etudiant2& student) {

}
