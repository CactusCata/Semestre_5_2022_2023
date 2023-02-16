#include "modalite.hpp"

Modalite::Modalite() {
    this->m = mod::CM;
    this->he = -1;
    this->capacite = -1;
    this->distanciel = true;
}

Modalite::Modalite(mod m, int he, int capacite){
    this->m = m;
    this->he = he;
    this->capacite = capacite;
    this->distanciel = true;
}

Modalite::Modalite(const Modalite &modalite) {
    this->m = modalite.m;
    this->he = modalite.he;
    this->capacite = modalite.capacite;
    this->distanciel = modalite.distanciel;
}

mod Modalite::Get_mod() const {
    return this->m;
}

int Modalite::Get_he() const {
    return this->he;
}

int Modalite::Get_capacite() const {
    return this->capacite;
}

bool Modalite::Get_distanciel() const {
    return this->distanciel;
}

void Modalite::covid() {
    if (this->Get_mod() == mod::TP) {
        if (!this->Get_distanciel()) {
            this->capacite = 16;
        }
    } else {
        if (!this->Get_distanciel()) {
            this->capacite *= 0.25;
        }
    }
}