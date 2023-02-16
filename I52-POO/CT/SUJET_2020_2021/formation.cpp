#include "formation.hpp"

Formation::Formation() {
    this->listeEcue = NULL;
    this->nbEcue = 0;
}

Formation::Formation(Ecue *listeEcue, int nbEcue) {
    this->listeEcue = new Ecue[nbEcue];

    for (int i = 0; i < nbEcue; i++) {
    this->listeEcue[i] = listeEcue[i]; 
    }

    this->nbEcue = nbEcue;
}

Formation::Formation(const Formation &formation):
Formation(formation.listeEcue, formation.nbEcue)
{

}

Formation::~Formation() {
    delete [] this->listeEcue;
}

Formation& Formation::operator=(const Formation &formation) {
    delete [] this->listeEcue;
    this->listeEcue = new Ecue[formation.nbEcue];

    for (int i = 0; i < formation.nbEcue; i++) {
    this->listeEcue[i] = formation.listeEcue[i]; 
    }

    this->nbEcue = nbEcue;
    return *this;
}

Ecue& Formation::operator[](int index) {
    return this->listeEcue[index];
}

int Formation::Get_nbEcue() const {
    return this->nbEcue;
}

void Formation::ajouter(const Ecue &ecue) {
    Ecue *newListe = new Ecue[this->Get_nbEcue() + 1];

    int i = 0;
    for (; i < this->Get_nbEcue(); i++) {
        newListe[i] = this->listeEcue[i];
    }
    newListe[i] = ecue;

    delete [] this->listeEcue;
    this->listeEcue = newListe;
    this->nbEcue++;
}