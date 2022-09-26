#include "mainExo3.hpp"

int main(int argc, char *argv[]) {

    std::ifstream vectDataFile("vectData.dat");

    if (!vectDataFile) {
        std::cout << "Le fichier n'a pas ete trouve !" << std::endl;
        exit(0);
    }

    VectorComplexe vect(vectDataFile);
    vect.print();


    Complexe z(12.0d, -56.0d);
    std::cout << z << std::endl;
}
