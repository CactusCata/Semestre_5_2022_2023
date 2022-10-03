#ifndef MATIERE_HPP
#define MATIERE_HPP

#include <string>
#include <iostream>

class Matiere {

    private:
        std::string nom;
        unsigned int coef;

    public:
        Matiere();
        Matiere(std::string nom, unsigned int coef);

        void print();
        std::string getNom();
        unsigned int getCoef();

};

#endif
