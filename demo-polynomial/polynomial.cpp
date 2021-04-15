#include "polynomial.h"

void Polynomial::push(const Monomial& n) //add_to_coef
{
    auto it = data.find(n.expo);
    if (it == data.end()) {
        data.insert({n.expo, n});
    } else {
        data[n.expo] += n;
    }
    return;
}

void Polynomial::modify_term_as(const Monomial& n)
{
    auto it = data.find(n.expo);
    if (it == data.end()) {
        data.insert({n.expo, n});
    } else {
        data[n.expo] = n;
    }
    return;
}

void Polynomial::add(const Polynomial& n)
{
    for (auto i : n.data) this->push(i.second);
}

void Polynomial::add(const Monomial& n)
{
    push(n);
}

void Polynomial::subtract(const Polynomial& n)
{
    for (auto i : n.data) push(-(i.second)); // or add(-i);
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
    std::map<frac, Monomial> tmp;
    for (auto i : this->data) {
        for (auto j : n.data) {
            auto term = i.second * j.second;
            tmp[term.expo] = term;
        }
    }
    data = tmp;
}

void Polynomial::multiply(const Monomial & n)
{
    std::map<frac, Monomial> tmp;
    for (auto i : this->data) {
        auto term = i.second * n;
        tmp[term.expo] = term;
    }
    data = tmp;
}

void Polynomial::derivate()
{
    std::map<frac, Monomial> tmp;
    for (auto i : this->data) {
        auto term = i.second;
        term.coef *= term.expo;
        term.expo -= 1;
        tmp[term.expo] = term;
    }
    data = tmp;
}

std::ostream& operator<<(std::ostream& stream, const Polynomial & m) {
    auto rit = m.data.rbegin();
    stream << (*rit).second;
    ++rit;
    for ( ; rit != m.data.rend(); ++rit) {
        if (rit->second.coef > 0) stream << " + ";
        else if (rit->second.coef < 0) stream << " ";
        stream << (*rit).second;
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
    for (auto i : data) {
        t += i.second.value(x);
    }
    return t;
}

Polynomial::Polynomial(const Polynomial & n)
{
    copy(n);
}
