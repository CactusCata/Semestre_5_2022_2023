#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <iostream>
#include <cmath>

class Complexe {

    public:

        double m_real, m_imaginary;

        Complexe();
        Complexe(double real, double imaginary);
        Complexe(const Complexe &z);

        ~Complexe();

        double getReal() const;
        double getImaginary() const;
        void setReal(double real);
        void setImaginary(double imaginary);
        Complexe getConjugue() const;
        double getModulo() const;
        void print() const;
        Comlexe Sum(const Complexe &z);
        Complexe& operator +=(const Complexe &z);
        Complexe& operator -=(const Complexe &z);
        Complexe& operator *=(const Complexe &z);
        Complexe& operator /=(const Complexe &z);
        Complexe operator +(const Complexe &z) const;
        Complexe operator -(const Complexe &z) const;
        Complexe operator *(const Complexe &z) const;
        Complexe operator /(const Complexe &z) const;
        bool operator ==(const Complexe &z) const;

        void Sum1(const Complexe& z);
        Complexe Sum2(const Complexe& z);
        Complexe Sum3(const Complexe& z);
        Complexe& Sum4(const Complexe& z);

};

#endif
