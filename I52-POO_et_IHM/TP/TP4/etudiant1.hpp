#ifndef ETUDIANT_1_HPP
#define ETUDIANT_1_HPP

#include "personne.hpp"

class Etudiant1 : public Personne {

    private:
        unsigned int nb;
        unsigned int *notes;

    public:
        Etudiant1(std::string nom, std::string prenom, unsigned int age, unsigned int nb);
        Etudiant1(const Etudiant1& student);
        ~Etudiant1();

        void ajouterNotes(unsigned int* notes);
        void print();
        double moyenne();

        Etudiant1& operator =(const Etudiant1& student);

};


#endif
