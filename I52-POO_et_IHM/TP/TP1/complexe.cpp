#include "complexe.hpp"

void afficherComplexe(const Complexe& c) {
    std::cout << "c(" << c.id << ") = " << c.a << " + i * " << c.b << std::endl;
}

Complexe Somme(const Complexe& c1, const Complexe& c2) {
    return {.id = generateID(), .a = c1.a + c2.a, .b = c1.b + c2.b};
}

Complexe Produit(const Complexe& c1, const Complexe& c2) {
    return {.id = generateID(), .a = c1.a * c2.a - c1.b * c2.b, .b = c1.b * c2.a + c1.a * c2.b};
}

float Module(const Complexe& c) {
    return static_cast<float>(c.a * c.a + c.b * c.b);
}

Complexe Conjuge(const Complexe& c) {
    return {.id = generateID(), .a = c.a, .b = -c.b};
}

unsigned int generateID() {
    static int idComplex = 0; // ou déclaration d'une variable globale
    return ++idComplex;
}

void Init(Complexe& c) {
    c.id = generateID();
    c.a = 0;
    c.b = 0;
}

Complexe Bidon(Complexe& c) {
    std::cout << "L'addresse de c est: " << &c << std::endl;
    std::cout << "L'addresse de c.id = " << &(c.id) << std::endl;
    std::cout << "L'addresse de c.a = " << &(c.a) << std::endl;
    std::cout << "L'addresse de c.b = " << &(c.b) << std::endl;
    return c;
}

void CreerComplexe(Complexe** c) {
    // Y'aura une étoile en trop ?
    c = new Complexe*;
    Complexe c1;
    Init(c1);
    *c = &c1;
}

void CreerComplexe(PtComplexe& ptr) {
    // Ce n'est pas la même fonction que celle d'au dessus
    // Ce n'est certainement pas ce qui était demandé
    Init(*ptr);
}

Complexe* CreerComplexe() {
    Complexe *c = new Complexe;
    Init(*c);
    return c;
}

Complexe* CreerVecteurComplexes(unsigned int size) {
    return new Complexe[size];
}