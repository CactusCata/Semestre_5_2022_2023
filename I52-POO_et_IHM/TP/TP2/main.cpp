#include "main.hpp"

int main(int argc, char *argv[]) {

    // exo4Bis();

    Complexe z1;
    std::cout << "Constructeur par defaut: " << std::endl;
    z1.print();

    Complexe z2(3, 8);
    z2.print();
    std::cout << "Conjugue de z2: " << std::endl;
    z2.getConjugue().print();
    std::cout << "Module de z2: " << z2.getModulo() << std::endl;


    Complexe z3(12, -8);
    std::cout << "z3 = " << std::endl;
    z3.print();

    Complexe z4 = z2 + z3;
    std::cout << "z2 + z3 = " << std::endl;
    z4.print();


}

void exo4Bis() {
    Complexe x(1,2);
    Complexe y(3,4);
    Complexe z(y);

    x.print(); // 1 + i2

    x.Sum1(y);
    x.print(); // 4 + i6

    (x.Sum2(y)).print(); // 7 + 10i (obj détruit + x n'est pas modifié)
    x.print(); // toujours le même x: 4 + i6

    ((x.Sum2(y)).Sum2(z)).print(); // 10 + i14 (obj détruit x2 + x n'est pas modifié)
    x.print(); // toujours le même x: 4 + i6

    ((x.Sum3(y)).Sum3(z)).print(); // 10 + i14 (La variable renvoyée est temporaire)
    x.print(); // x modifié une fois (pendant x.Sum3(y), ensuite le .Sum(3) travail sur une copie de x)  7 + i10

    ((x.Sum4(y)).Sum4(z)).print(); // 13 + i18
    x.print(); // 13 + i18

    // On va choisir la dernière méthode
}
