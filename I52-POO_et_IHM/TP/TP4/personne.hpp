#ifndef PERSONNE_HPP
#define PERSONNE_HPP

#include <string>
#include <iostream>

class Personne {

    private:
        std::string m_nom;
        std::string m_prenom;
        unsigned int m_age;

    public:
        Personne(std::string nom, std::string prenom, unsigned int age);
        void print() const;
        void ageing();

};

#endif
