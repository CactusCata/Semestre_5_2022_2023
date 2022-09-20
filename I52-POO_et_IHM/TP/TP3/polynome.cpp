#include "polynome.hpp"

Polynome::Polynome(unsigned int degre, double *coefs) {
    this->m_degre = degre;

    this->m_coefs = new double[this->m_degre + 1];
    for (unsigned int i = 0; i < this->m_degre + 1; i++) {
        this->m_coefs[i] = coefs[i];
    }
}

Polynome::Polynome() {
    this->m_degre = 0;
    this->m_coefs = NULL;
}

Polynome::Polynome(const Polynome &poly):
Polynome(poly.m_degre, poly.m_coefs)
{
}

Polynome::~Polynome() {
    delete [] this->m_coefs;
}

Polynome Polynome::operator =(const Polynome& z) {
    return Polynome(z);
}

double Polynome::eval(const double &x) const {
    /**
    *   taille de m_coefs = m_degre + 1
    *   [2, 4, -6, 1]
    *   2x^3 + 4x^2 - 6x^1 + 3x^0
    * = (((2) * x + 4) * x + 6) * x + 3
    */
    double res = m_coefs[0];
    for (unsigned int i = 1; i < this->m_degre + 1; i++) {
        res *= x;
        res += this->m_coefs[i];
    }
    return res;
}
