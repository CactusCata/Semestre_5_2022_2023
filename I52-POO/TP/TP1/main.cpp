#include <iostream>
#include "echangiste.hpp"
#include "complexe.hpp"

int main(int argc, char **argv) {
    int a = 12;
    int b = 17;

    std::cout << "Valeur de a: " << a << std::endl;
    std::cout << "Valeur de b: " << b << std::endl;

    permuter(a, b);

    std::cout << "Valeur de a: " << a << std::endl;
    std::cout << "Valeur de b: " << b << std::endl;


    Complexe c1;
    Init(c1);
    c1.a = 5.3f;
    c1.b = 8.6f;
    Complexe c2;
    Init(c2);
    c2.a = -186.0f;
    c2.b = 12.3f;

    afficherComplexe(c1);
    afficherComplexe(c2);

    permuter(c1, c2);

    afficherComplexe(c1);
    afficherComplexe(c2);

    permuter(c1, c2);

    afficherComplexe(Somme(c1, c1));
    afficherComplexe(Produit(c1, c1));

    // Utilisation d'une autre formule: le module des produits de complexe
    // est égale au produit des modules
    std::cout << Module(Produit(c1, c2)) << std::endl;
    float c1Mod = Module(c1);
    float c2Mod = Module(c2);
    std::cout << (c1Mod * c2Mod) << std::endl;

    static Complexe c5;
    Init(c5);

    // Question 4.2
    // On remarque que l'addresse de c5 est la même que son premier champs (à revérifier)
    std::cout << "L'addresse de c5 est: " << &c5 << std::endl;
    std::cout << "L'addresse de c5.id = " << &(c5.id) << std::endl;
    std::cout << "L'addresse de c5.a = " << &(c5.a) << std::endl;
    std::cout << "L'addresse de c5.b = " << &(c5.b) << std::endl;

    std::cout << std::endl;

    // Lorsque on fait une référence, les champs fils sont égalements recopiés par
    // référence
    Complexe &c6 = c5;
    std::cout << "L'addresse de c6 est: " << &c6 << std::endl;
    std::cout << "L'addresse de c6.id = " << &(c6.id) << std::endl;
    std::cout << "L'addresse de c6.a = " << &(c6.a) << std::endl;
    std::cout << "L'addresse de c6.b = " << &(c6.b) << std::endl;

    std::cout << std::endl;

    // Suite de la question
    // On remarque que le complexe de retour est une copie
    // de celui mit en entrée
    Complexe c7;
    Init(c7);

    Complexe c8 = Bidon(c7);

    std::cout << std::endl;

    std::cout << "L'addresse de c8 est: " << &c8 << std::endl;
    std::cout << "L'addresse de c8.id = " << &(c8.id) << std::endl;
    std::cout << "L'addresse de c8.a = " << &(c8.a) << std::endl;
    std::cout << "L'addresse de c8.b = " << &(c8.b) << std::endl;


    Complexe *pt;
    creerComplexe(&pt);



}
