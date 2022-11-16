#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <iostream>
#include <cmath>

typedef struct Complexe {
    // Comment optimiser le coût mémoire de cette fonctionnalité ? AUCUNE IDEE, PAS COMPRIS, remplir le champs grace à son adresse ?
    unsigned int id;

    float a; // partie réelle
    float b; // partie imaginaire
} Complexe;

typedef Complexe* PtComplexe;

void afficherComplexe(const Complexe&);
/**
 * Le rôle joué par l'opérateur '&' est de ne pas faire une
 * copie de la valeur de complexe (fait par défaut).
 * 
 * Le rôle joué par l'opérateur const est que la variable ne
 * sera pas modifiable.
 * 
 * C'est un processus qui permet d'optimiser le code.
 */

Complexe Somme(const Complexe&, const Complexe&);

Complexe Produit(const Complexe&, const Complexe&);

float Module(const Complexe&);

Complexe Conjuge(const Complexe&);

void Init(Complexe&);

unsigned int generateID();

Complexe Bidon(Complexe&);

void CreerComplexe(Complexe**);

Complexe* CreerComplexe();

Complexe* CreerVecteurComplexes(unsigned int);

#endif