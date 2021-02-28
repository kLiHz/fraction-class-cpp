#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <iostream>
#include <cmath>
#include <list>
#include "monomial.h"

class Polynomial
{
    std::list<Monomial> data; //terms are stored from smaller expo to bigger expo
public:
    void push(const Monomial &);
    void modify_term_as(const Monomial &);
    void add(const Monomial &);
    void add(const Polynomial &);
    void subtract(const Monomial &);
    void subtract(const Polynomial &);
    void multiply(const Monomial &);
    void multiply(const Polynomial &);
    void derivate();

    void copy(const Polynomial &);
    void clear();
    double value(double val);

    void operator= (const Polynomial &);

    // friend std::string to_string(const Monomial &);
    friend std::ostream& operator<<(std::ostream&, const Polynomial &);

    Polynomial() = default;
    Polynomial(const Polynomial &);
    ~Polynomial() = default;
};

#endif
