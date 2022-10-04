#ifndef ETUDIANT_HPP
#define ETUDIANT_HPP

#include "personne.hpp"
#include "cursus.hpp"
#include <string>

class Etudiant : public Personne {

  private:
    Cursus cursus;

  public:
    Etudiant(std::string nom, std::string prenom, unsigned int age, Cursus cursus);
    Etudiant();
    Etudiant(const Etudiant &etudiant);
    ~Etudiant();

    Etudiant &operator =(const Etudiant &etudiant);



};


#endif
