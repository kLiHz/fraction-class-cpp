#include "polynomial.h"

void Polynomial::push(const Monomial& n) //add_to_coef
{
    bool has_insert = false;
    std::list<Monomial>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        if (n == *it) //equal expo term found
        {
            *it += n;
            has_insert = true;
            break;
        }
        else if (n < *it) //now expo is bigger
        {
            data.insert(it,n);
            has_insert = true;
            break;
        }
        else continue;
    }
    if (!has_insert)
    {
        data.push_back(n);
    }
    return;
}

void Polynomial::modify_term_as(const Monomial& n)
{
    bool has_insert = false;
    std::list<Monomial>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        if (*it == n) 
        {
            *it = n;
            has_insert = true;
            break;
        }
        else if (n < *it)
        {
            data.insert(it,n);
            has_insert = true;
            break;
        }
        else continue;
    }
    if (!has_insert)
    {
        data.push_back(n);
    }
    return;
}
void Polynomial::add(const Polynomial& n)
{
    for (auto i : n.data) this->push(i);
}
void Polynomial::add(const Monomial& n)
{
    push(n);
}
void Polynomial::subtract(const Polynomial& n)
{
    for (auto i : n.data) push(-i); // or add(-i);
}
void Polynomial::subtract(const Monomial& n)
{
    push(-n);
}

void Polynomial::copy(const Polynomial & n)
{
    data = n.data;
}

void Polynomial::operator=(const Polynomial& n)
{
    data = n.data;
}

void Polynomial::multiply(const Polynomial & n)
{
    std::list<Monomial> tmp;
    for (auto i : this->data) {
        for (auto j : n.data) {
            tmp.push_back(i * j);
        }
    }
    tmp.sort();
    data = tmp;
}

void Polynomial::multiply(const Monomial & n)
{
    std::list<Monomial>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        (*it) *= n;
    }
    //data.sort();
}

void Polynomial::derivate()
{
    std::list<Monomial>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        it->coef *= it->expo;
        it->expo -= 1; 
    }
}

std::ostream& operator<<(std::ostream& stream, const Polynomial & m) {
    auto rit = m.data.rbegin();
    stream << *rit;
    ++rit;
    for ( ; rit != m.data.rend(); ++rit) {
        if (rit->coef > 0) stream << " + ";
        else if (rit->coef < 0) stream << " ";
        stream << *rit;
    }
    return stream;
}

void Polynomial::clear()
{
    data.clear();
}

double Polynomial::value(double x)
{
    double t = 0;
    std::list<Monomial>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        t += it->value(x);
    }
    return t;
}

Polynomial::Polynomial(const Polynomial & n)
{
    copy(n);
}
