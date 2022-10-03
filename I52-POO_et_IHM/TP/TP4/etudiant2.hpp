#ifndef ETUDIANT_2_HPP
#define ETUDIANT_2_HPP

#include "matiere.hpp"
#include "etudiant1.hpp"
#include <ostream>

class Etudiant2 : public Etudiant1 {

    private:
        Matiere *matieres;

    public:
        Etudiant2(std::string nom, std::string prenom, unsigned int age, unsigned int nb, Matiere *matieres);
        Etudiant2(const Etudiant2& student);
        ~Etudiant2();

        void print();
        double moyenne();

        Etudiant2 &operator =(const Etudiant2& student);

};

#endif
