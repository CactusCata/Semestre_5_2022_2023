#include "complexe.hpp"

Complexe::Complexe(double real, double imaginary) {
    this->setReal(real);
    this->setImaginary(imaginary);
}

Complexe::Complexe():
Complexe(0, 0)
{

}

Complexe::Complexe(const Complexe &z):
Complexe(z.getReal(), z.getImaginary())
{

}

Complexe::~Complexe() {
    std::cerr << "Destructeur de complexe appele" << std::endl;
}

double Complexe::getReal() const {
    return this->m_real;
}

double Complexe::getImaginary() const {
    return this->m_imaginary;
}

void Complexe::setReal(double real) {
    this->m_real = real;
}

void Complexe::setImaginary(double imaginary) {
    this->m_imaginary = imaginary;
}

Complexe Complexe::getConjugue() const {
    Complexe z(this->getReal(), -this->getImaginary());
    return z;
}

double Complexe::getModulo() const {
    return sqrt(this->getReal() * this->getReal() + this->getImaginary() * this->getImaginary());
}

void Complexe::print() const {
    std::cout << this->getReal() << "+i" << this->getImaginary() << std::endl; 
}

Complexe Complexe::operator +=(const Complexe &z) {
    this->setReal(this->getReal() + z.getReal());
    this->setImaginary(this->getImaginary() + z.getImaginary());
    return *this;
}

Complexe Complexe::operator -=(const Complexe &z) {
    this->setReal(this->getReal() - z.getReal());
    this->setImaginary(this->getImaginary() - z.getImaginary());
    return *this;
}

Complexe Complexe::operator *=(const Complexe &z) {
    this->setReal(this->getReal() * z.getReal() - this->getImaginary() * z.getImaginary());
    this->setImaginary(this->getReal() * z.getImaginary() + z.getReal() * this->getImaginary());
    return *this;
}

Complexe Complexe::operator /=(const Complexe &z) {
    Complexe conjugeZ = z.getConjugue();
    (*this) *= conjugeZ;
    double deno = z.getReal() * z.getReal() - z.getImaginary() * z.getImaginary();
    this->setReal(this->getReal() / deno);
    this->setImaginary(this->getImaginary() / deno);
    return *this;
}

Complexe Complexe::operator +(const Complexe &z) const {
    Complexe z1(z);
    return z1 += *this;
}

Complexe Complexe::operator -(const Complexe &z) const {
    Complexe z1(z);
    return z1 -= *this;
}

Complexe Complexe::operator *(const Complexe &z) const {
    Complexe z1(z);
    return z1 *= *this;
}

Complexe Complexe::operator /(const Complexe &z) const {
    Complexe z1(z);
    return z1 /= *this;
}


bool Complexe::operator ==(const Complexe &z) const {
    return this->getReal() == z.getReal() && this->getImaginary() == z.getImaginary();
}

void Complexe::Sum1(const Complexe& z) {
    m_real = m_real + z.m_real;
    m_imaginary = m_imaginary + z.m_imaginary;
}

Complexe Complexe::Sum2(const Complexe& z) {
    return Complexe(m_real + z.m_real, m_imaginary + z.m_imaginary);
}

Complexe Complexe::Sum3(const Complexe& z) {
    m_real = m_real + z.m_real;
    m_imaginary = m_imaginary + z.m_imaginary;
    return *this;
}

Complexe& Complexe::Sum4(const Complexe& z) {
    m_real = m_real + z.m_real;
    m_imaginary = m_imaginary + z.m_imaginary;
    return *this;
}
