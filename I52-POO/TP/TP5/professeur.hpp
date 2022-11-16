#ifndef PROFESSEUR_CPP
#define PROFESSEUR_CPP

#include "personne.hpp"
#include "matiere.hpp"

class Professeur : public Personne {

  private:
    Matiere *liste_enseignements;
    unsigned int liste_enseignements_size;

  public:
    Professeur(std::string nom, std::string prenom, unsigned int age, Matiere *liste_enseignements, unsigned int liste_enseignements_size);
    Professeur();
    Professeur(const Professeur &professeur);
    ~Professeur();

    Professeur &operator =(const Professeur &professeur);

};

#endif
