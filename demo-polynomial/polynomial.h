#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <iostream>
#include <cmath>
#include <list>
#include "../fraction.h"
#include "monomial.h"

class polynomial
{
    std::list<monomial> data;
public:
    void push(monomial& );
    void modify(monomial& );
    void add(polynomial& );
    void subtract(polynomial& );
    void add(monomial& );
    void subtract(monomial& );
    void multiply(monomial& );
    void multiply(polynomial& );
    void derivate();

    void copy(polynomial& );
    void clear();
    double value(double );

    void print();
    void operator= (polynomial& );

    polynomial();
    polynomial(polynomial& );
    ~polynomial();
};

#endif