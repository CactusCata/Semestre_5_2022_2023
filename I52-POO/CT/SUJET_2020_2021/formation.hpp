#ifndef FORMATION_H
#define FORMATION_H

#include "ecue.hpp"

class Formation {

    private:
        Ecue *listeEcue;
        int nbEcue;

    public:
        Formation();
        Formation(Ecue *listeEcue, int nbEcue);
        Formation(const Formation &formation);
        ~Formation();

        Formation& operator=(const Formation &formation);
        Ecue& operator[](int index);  

        int Get_nbEcue() const;

        void ajouter(const Ecue &ecue);


};

#endif