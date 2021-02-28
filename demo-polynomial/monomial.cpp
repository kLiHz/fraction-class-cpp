#include "monomial.h"

void Monomial::multiply(const Monomial& t)
{
    coef *= t.coef;
    expo += t.expo;
}
void Monomial::divide(const Monomial& t)
{
    coef /= t.coef;
    expo -= t.expo;
}
double Monomial::value(double x)
{
    return double(coef) * pow(x, expo);
}
Monomial Monomial::operator*(const Monomial& t) const
{
    Monomial tmp(coef,expo);
    tmp.multiply(t);
    return tmp;
}
Monomial& Monomial::operator*=(const Monomial& t)
{
    multiply(t);
    return *this;
}
Monomial Monomial::operator+(const Monomial & t) const
{
    return Monomial(coef + t.coef, expo);
}
Monomial & Monomial::operator+=(const Monomial & t)
{
    coef += t.coef;
    return *this;
}
Monomial Monomial::operator-() const
{
    return Monomial(-coef, expo);
}
Monomial Monomial::operator-(const Monomial & t) const
{
    return Monomial(coef - t.coef, expo);
}
Monomial & Monomial::operator-=(const Monomial & t)
{
    coef -= t.coef;
    return *this;
}

std::string to_string(const Monomial & m) {
    std::string str;
    if (m.coef == 0) return str;
    if (m.expo == 0) return to_string(m.coef);
    if (m.coef == -1) { str += "-"; }
    else if (m.coef != 1) {
        str += to_string(m.coef);
        str += ' ';
        str += 'x';
    }
    if (m.expo != 1) {
        str += "^";
        if (m.expo < 0 || !(m.expo.is_int())) {
            str += "(";
            str += to_string(m.expo);
            str += ")";
        }
        else str += to_string(m.expo);
    }
}

std::ostream& operator<<(std::ostream& stream, const Monomial & m) {
    stream << to_string(m);
}

bool Monomial::operator<(const Monomial & t) const
{
    return expo < t.expo;
}

bool Monomial::operator==(const Monomial & t) const
{
    return expo == t.expo;
}

bool Monomial::operator>(const Monomial & t) const
{
    return expo > t.expo;
}

bool Monomial::operator!=(const Monomial & t) const
{
    return expo != t.expo;
}

