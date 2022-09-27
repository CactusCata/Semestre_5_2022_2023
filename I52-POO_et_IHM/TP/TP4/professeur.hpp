#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

#include "personne.hpp"

class Professor : public Personne {

    private:
      std::string statut;
      unsigned int heures;


    public:
      Professor(std::string nom, std::string prenom, unsigned int age, std::string statut);
      void print();
      void work(unsigned int hourCount);


};

#endif
