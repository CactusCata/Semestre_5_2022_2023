#ifndef CURSUS_HPP
#define CURSUS_HPP

#include <string>
#include "matiere.hpp"
#include "professeur.hpp"

class Cursus {

  private:
    std::string intitule;
    Professeur responsable;
    Matiere *liste_matieres;
    unsigned int liste_matieres_size;

  public:
    Cursus(std::string intitule, const Professeur &responsable, Matiere *liste_matiere, unsigned int liste_matieres_size);
    Cursus();
    Cursus(const Cursus &cursus);
    ~Cursus();

    Cursus &operator =(const Cursus &cursus);
};

#endif
