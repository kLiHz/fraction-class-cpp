#include "polynomial.h"
using namespace std;

void polynomial::push(const monomial& n) //add_to_coef
{
    bool has_insert = false;
    std::list<monomial>::iterator it;
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

void polynomial::modify_term_as(const monomial& n)
{
    bool has_insert = false;
    std::list<monomial>::iterator it;
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
void polynomial::add(polynomial& n)
{
    std::list<monomial>::iterator it;
    for (it = n.data.begin(); it != n.data.end(); ++it)
    {
        push(*it);
    }
}
void polynomial::add(const monomial& n)
{
    push(n);
}
void polynomial::subtract(polynomial& n)
{
    std::list<monomial>::iterator it;
    for (it = n.data.begin(); it != n.data.end(); ++it)
    {
        push(-(*it)); // or add(-(*it));
    }
}
void polynomial::subtract(const monomial& n)
{
    push(-n);
}

void polynomial::copy(const polynomial & n)
{
    data = n.data;
}

void polynomial::operator=(const polynomial& n)
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

void polynomial::multiply(const monomial & n)
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
        it->expo -= 1; 
    }
}

void polynomial::print()
{
    bool flag = false;
    for (std::list<monomial>::reverse_iterator rit = data.rbegin(); rit!=data.rend(); ++rit)
    {
        if (flag && rit->coef > 0) cout << " + ";
        rit->print();
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
polynomial::polynomial(const polynomial & n)
{
    copy(n);
}
polynomial::~polynomial(){}