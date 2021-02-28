#ifndef _MONOMIAL_H_
#define _MONOMIAL_H_

#include <iostream>
#include <string.h>
#include <cmath>
#include "fraction.h"

class Monomial
{
public:
#ifdef _FRACTION_H_
    fraction coef;
    fraction expo;
    Monomial(const fraction & a, const fraction & b ): coef(a), expo(b) {}
#else
    double coef;
    double expo;
    Monomial(double a, double b) : coef(a), expo(b) {}
#endif

    void multiply(const Monomial &);
    void divide(const Monomial &);
    double value(double);

    Monomial operator+(const Monomial &) const;
    Monomial operator-(const Monomial &) const;
    Monomial operator*(const Monomial &) const;
    Monomial operator-() const;
    Monomial & operator+=(const Monomial &);
    Monomial & operator*=(const Monomial &);
    Monomial & operator-=(const Monomial &);
    
    bool operator<(const Monomial &) const; //compare by exponent
    bool operator>(const Monomial &) const;
    bool operator==(const Monomial &) const; //compare by exponent
    bool operator!=(const Monomial &) const;
    
    friend std::string to_string(const Monomial &);
    friend std::ostream& operator<<(std::ostream&, const Monomial &);

    Monomial() : coef(0), expo(0) {}
};

#endif
