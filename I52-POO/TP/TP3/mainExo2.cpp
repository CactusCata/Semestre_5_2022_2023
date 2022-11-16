#include "mainExo2.hpp"

int main(int argc, char *argv[]) {

    double *coefs = new double[3]{1.0d, 2.0d, 3.0d};
    Polynome p(2, coefs);
    std::cout << p.eval(5.0d) << std::endl;

}
