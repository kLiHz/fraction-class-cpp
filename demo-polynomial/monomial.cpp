#include "monomial.h"
using namespace std;

void monomial::multiply(const monomial& t)
{
    //coef.multiply(t.coef);
    //expo.add(t.expo);
    coef *= t.coef;
    expo += t.expo;
}
void monomial::divide(const monomial& t)
{
    //coef.divide(t.coef);
    //expo.subtract(t.expo);
    coef /= t.coef;
    expo -= t.expo;
}
double monomial::value(double x)
{
    return coef.value()*pow(x,expo.value());
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
    if (expo.value() == 0) 
    {
        //coef.print();
        cout << coef;
        return;
    }
    if (abs(coef.value()) == 1)
    {
        if (coef.value() < 0) cout << " - ";
    }
    //else coef.print();
    else cout << coef;
    cout<<' '<<'x';
    if (expo.value() != 1)
    {
        cout<<"^";
        if (!expo.if_int() || expo < 0)
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

//monomial::monomial(int a, int b): coef(a), expo(b){}
//monomial::monomial(fraction& a, int b):coef(a), expo(b){}
//monomial::monomial(int a, fraction& b):coef(a), expo(b){}

monomial::monomial(const fraction & a, const fraction & b ): coef(a), expo(b) {}
//monomial::monomial(const string & a, const string & b): coef(a), expo(b) {}