#ifndef POLYNOME_HPP
#define POLYNOME_HPP

#include <cstddef>
#include <iostream>

class Polynome {

    private:
        unsigned int m_degre;
        double *m_coefs;
        /**
        *   taille de m_coefs = m_degre + 1
        *   [2, 4, -6, 1]
        *   2x^3 + 4x^2 - 6x^1 + 3x^0
        * = (((2) * x + 4) * x + 6) * x + 3
        */

    public:

        Polynome();
        Polynome(unsigned int taille, double *array);
        Polynome(const Polynome& poly);
        ~Polynome();

        Polynome operator =(const Polynome& z);

        double eval(const double &x) const;

};

#endif

/**
  * EXERCICE 2
  *
  * Au niveau des constructeur, il va falloir allouer dynamiquement
  * à l'air du mot-clef new.
  *
  * Au niveau du constructeur par recopie, l'adresse va être copiée
  * et les deux tableaux poités seront les mêmes.
  *
  * Le destructeur va permettre d'éviter une fuite de mémoire.
  *
*/
