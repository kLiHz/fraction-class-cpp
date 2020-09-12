#include "polynomial.h"
using namespace std;

void polynomial::push(monomial& n) //add_to_coef
{
    std::list<monomial>::iterator it;
    bool found_similar_item = false;
    for (it = data.begin(); it != data.end(); ++it)
    {
        if (*it == n) 
        {
            found_similar_item = true;
            *it += n;
            break;
        }
    }
    if (!found_similar_item)
    {
        data.push_back(n);
        data.sort();
    }
}

void polynomial::modify(monomial& n)
{
    std::list<monomial>::iterator it;
    bool found_similar_item = false;
    for (it = data.begin(); it != data.end(); ++it)
    {
        if (*it == n) 
        {
            found_similar_item = true;
            *it = n;
            break;
        }
    }
    if (!found_similar_item)
    {
        data.push_back(n);
        data.sort();
    }
}
void polynomial::add(polynomial& n)
{
    std::list<monomial>::iterator it;
    for (it = n.data.begin(); it != n.data.end(); ++it)
    {
        push(*it);
    }
}
void polynomial::add(monomial& n)
{
    push(n);
}
void polynomial::subtract(polynomial& n)
{
    std::list<monomial>::iterator it;
    for (it = n.data.begin(); it != n.data.end(); ++it)
    {
        monomial t = *it;
        t.coef = 0 - t.coef;
        push(t);
    }
}
void polynomial::subtract(monomial& n)
{
    monomial t(n);
    t.coef = 0 - t.coef;
    push(t);
}

void polynomial::copy(polynomial & n)
{
    data = n.data;
}

void polynomial::operator=(polynomial& n)
{
    data = n.data;
}

void polynomial::multiply(polynomial & n)
{
    std::list<monomial>::iterator it1, it2;
    list<monomial> tmp;
    for (it1 = data.begin(); it1 != data.end(); ++it1)
    {
        for (it2 = n.data.begin(); it2 != n.data.end(); ++it2)
        {
            tmp.push_back((*it1) * (*it2));
        }
    }
    tmp.sort();
    data = tmp;
}

void polynomial::multiply(monomial & n)
{
    std::list<monomial>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        (*it) *= n;
    }
    //data.sort();
}
void polynomial::derivate()
{
    std::list<monomial>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        it->coef *= it->expo;
        it->expo -=1; 
    }
}

void polynomial::print()
{
    bool flag = false;
    std::list<monomial>::iterator it;
    for (it = data.end(); it != data.begin(); --it)
    {
        if (flag && it->coef.value() > 0) cout << " + ";
        it->print();
        flag = true;
    }
}

void polynomial::clear()
{
    data.clear();
}

double polynomial::value(double x)
{
    double t = 0;
    std::list<monomial>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        t += it->coef.value() * pow(x, it->expo.value());
    }
    return t;
}

polynomial::polynomial(){}
polynomial::polynomial(polynomial & n)
{
    copy(n);
}
polynomial::~polynomial(){}