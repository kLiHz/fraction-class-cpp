#ifndef _MONOMIAL_H_
#define _MONOMIAL_H_

#include <iostream>
#include <string.h>
#include <cmath>
#include "../fraction.h"

class monomial
{
public:
    fraction coef;
    fraction expo;
    void print();

    void multiply(const monomial &);
    void divide(const monomial &);
    double value(double );

    monomial operator+(const monomial &) const;
    monomial operator-(const monomial &) const;
    monomial operator*(const monomial &) const;
    monomial operator-() const;
    monomial & operator+=(const monomial &);
    monomial & operator*=(const monomial &);
    monomial & operator-=(const monomial &);
    
    bool operator<(const monomial &) const; //compare by exponent
    bool operator>(const monomial &) const;
    bool operator==(const monomial &) const; //compare by exponent
    bool operator!=(const monomial &) const;
    
    monomial();
    //monomial(int, int);
    //monomial(fraction&, int );
    //monomial(int, fraction& );
    monomial(const fraction&, const fraction& );
    //monomial(const std::string &, const std::string &);
};

#endif