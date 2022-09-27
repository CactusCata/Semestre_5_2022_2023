#include "complexe.hpp"

static Complexe zLocalFile(2, 3);

Complexe::Complexe(double real, double imaginary) {
    this->setReal(real);
    this->setImaginary(imaginary);
    std::cout << "Creation d'un constructeur: (" << this->getReal() << ',' << this->getImaginary() << ')' << std::endl;

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
    std::cout << "Appelle d'un destructeur: (" << this->getReal() << ',' << this->getImaginary() << ')' << std::endl;
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
    return Complexe(this->getReal(), -this->getImaginary());
}

double Complexe::getModulo() const {
    return sqrt(this->getReal() * this->getReal() + this->getImaginary() * this->getImaginary());
}

std::string Complexe::print() const {
    std::string serialized;
    serialized.append(std::to_string(this->getReal()));
    char sign = '+';
    float imgAbs = this->getImaginary();
    if (imgAbs < 0) {
      sign = '-';
      imgAbs *= -1;
    }
    serialized.push_back(sign);
    serialized.append("ix");
    serialized.append(std::to_string(imgAbs));
    return serialized;
}

Complexe& Complexe::Sum(const Complexe &z) {
    return *this += z;
}

Complexe& Complexe::operator +=(const Complexe &z) {
    this->setReal(this->getReal() + z.getReal());
    this->setImaginary(this->getImaginary() + z.getImaginary());
    return *this;
}

Complexe& Complexe::operator -=(const Complexe &z) {
    this->setReal(this->getReal() - z.getReal());
    this->setImaginary(this->getImaginary() - z.getImaginary());
    return *this;
}

Complexe& Complexe::operator *=(const Complexe &z) {
    this->setReal(this->getReal() * z.getReal() - this->getImaginary() * z.getImaginary());
    this->setImaginary(this->getReal() * z.getImaginary() + z.getReal() * this->getImaginary());
    return *this;
}

Complexe& Complexe::operator /=(const Complexe &z) {
    Complexe conjugeZ = z.getConjugue();
    (*this) *= conjugeZ;
    double deno = z.getReal() * z.getReal() - z.getImaginary() * z.getImaginary();
    this->setReal(this->getReal() / deno);
    this->setImaginary(this->getImaginary() / deno);
    return *this;
}


Complexe operator *(const Complexe& z, const int& k) {
    return Complexe(z.getReal() * k, z.getImaginary() * k);
}

Complexe operator *(const int& k, const Complexe& z) {
    return z * k;
}

std::ostream &operator <<(std::ostream& stream, const Complexe& z) {
    return stream << z.getReal() << z.getImaginary();
}

Complexe Complexe::operator +(const Complexe &z) const {
    return Complexe(this->getReal() + z.getReal(), this->getImaginary() + z.getImaginary());
}

Complexe Complexe::operator -(const Complexe &z) const {
    return Complexe(this->getReal() - z.getReal(), this->getImaginary() - z.getImaginary());
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
