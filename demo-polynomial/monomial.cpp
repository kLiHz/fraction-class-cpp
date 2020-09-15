#include "monomial.h"
using namespace std;

void monomial::multiply(const monomial& t)
{
    coef *= t.coef;
    expo += t.expo;
}
void monomial::divide(const monomial& t)
{
    coef /= t.coef;
    expo -= t.expo;
}
double monomial::value(double x)
{
    return double(coef) * pow(x, expo);
}
monomial monomial::operator*(const monomial& t) const
{
    monomial tmp(coef,expo);
    tmp.multiply(t);
    return tmp;
}
monomial& monomial::operator*=(const monomial& t)
{
    multiply(t);
    return *this;
}
monomial monomial::operator+(const monomial & t) const
{
    return monomial(coef + t.coef, expo);
}
monomial & monomial::operator+=(const monomial & t)
{
    coef += t.coef;
    return *this;
}
monomial monomial::operator-() const
{
    return monomial(-coef, expo);
}
monomial monomial::operator-(const monomial & t) const
{
    return monomial(coef - t.coef, expo);
}
monomial & monomial::operator-=(const monomial & t)
{
    coef -= t.coef;
    return *this;
}

void monomial::print()
{
    if (coef == 0) return;
    if (expo == 0) 
    {
        //coef.print();
        cout << coef;
        return;
    }
    if (abs(coef) == 1)
    {
        if (coef < 0) cout << " - ";
    }
    //else coef.print();
    else cout << coef;
    cout << ' ' << 'x';
    if (expo != 1)
    {
        cout << "^";
#ifdef _FRACTION_H_
        if (!expo.if_int())
#endif
        if (expo < 0)
        {
            cout << "(";
            //expo.print(); 
            cout << expo;
            cout << ")";
        }
        //else expo.print();
        else cout << expo;
    }
}

bool monomial::operator<(const monomial & t) const
{
    return expo < t.expo;
}

bool monomial::operator==(const monomial & t) const
{
    return expo == t.expo;
}

bool monomial::operator>(const monomial & t) const
{
    return expo > t.expo;
}

bool monomial::operator!=(const monomial & t) const
{
    return expo != t.expo;
}

monomial::monomial(): coef(0), expo(0) {}

#ifdef _FRACTION_H_
monomial::monomial(const fraction & a, const fraction & b ): coef(a), expo(b) {}
#else
monomial::monomial(double a, double b) : coef(a), expo(b) {}
#endif

//monomial::monomial(int a, int b): coef(a), expo(b){}
//monomial::monomial(fraction& a, int b):coef(a), expo(b){}
//monomial::monomial(int a, fraction& b):coef(a), expo(b){}

//monomial::monomial(const string & a, const string & b): coef(a), expo(b) {}