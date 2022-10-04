#ifndef PERSONNE_HPP
#define PERSONNE_HPP

#include <string>
#include <iostream>

class Personne {

  private:
    std::string nom, prenom;
    unsigned int age;

  public:
    Personne(std::string nom, std::string prenom, unsigned int age);
    Personne(const Personne &p);
    Personne();
    ~Personne();

    Personne &operator =(const Personne &p);

    friend std::ostream &operator <<(std::ostream &stream, const Personne& personne);

};

#endif
