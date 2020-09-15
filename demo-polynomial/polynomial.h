#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <iostream>
#include <cmath>
#include <list>
#include "monomial.h"

class polynomial
{
    std::list<monomial> data; //terms are stored from smaller expo to bigger expo
public:
    void push(const monomial &);
    void modify_term_as(const monomial &);
    void add(/*const*/ polynomial &);
    void add(const monomial &);
    void subtract(/*const*/ polynomial &);
    void subtract(const monomial &);
    void multiply(const monomial &);
    void multiply(/*const*/ polynomial &);
    void derivate();

    void copy(const polynomial &);
    void clear();
    double value(double );

    void print();
    void operator= (const polynomial &);

    polynomial();
    polynomial(const polynomial &);
    ~polynomial();
};

#endif