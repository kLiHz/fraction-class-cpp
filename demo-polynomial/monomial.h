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

    void multiply(monomial &);
    void divide(monomial &);
    double value(double );

    monomial operator*(monomial &);
    monomial & operator*=(monomial &);
    monomial operator+(monomial &);
    monomial & operator+=(monomial &);
    monomial operator-(monomial &);
    monomial & operator-=(monomial &);
    
    bool operator<(monomial &); //compare by exponent
    bool operator==(monomial &); //compare by exponent
    
    monomial();
    //monomial(int, int);
    //monomial(fraction&, int );
    //monomial(int, fraction& );
    monomial(const fraction&, const fraction& );
    monomial(const std::string &, const std::string &);
};

#endif