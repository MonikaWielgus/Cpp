//Monika Wielgus
#include <iostream>
#include <sstream>
#include "Z2.h"
#ifndef Wielomian_h
#define Wielomian_h

class Polynomial{
    public:
    unsigned int degree;
    Z2 *coef;

    Polynomial();
    Polynomial(unsigned int a, Z2 *tab);
    short int operator[](unsigned int index) const;
    unsigned int deg() const;
    std::string toString(std::string xVar);
};

Polynomial operator+(const Polynomial &a, const Polynomial &b);
Polynomial operator*(const Polynomial &a, const Polynomial &b);
std::ostream& operator<<(std::ostream& out, const Polynomial& x);
std::istream& operator>>(std::istream& in, Polynomial& x);
#endif
