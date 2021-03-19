#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

class fraction
{
private:
    int A;  //numerator
    int B;  //denominator
public:
    static int gcd(int, int);
    static int lcm(int, int);
    void reduce();
    bool is_int() const;

    fraction & add(const fraction& );
    fraction & add(int );
    fraction & subtract(const fraction& );
    fraction & multiply(const fraction& );
    fraction & divide(const fraction& );
    double value() const;

    fraction operator+ (const fraction& ) const;
    fraction operator- (const fraction& ) const;
    fraction operator* (const fraction& ) const;
    fraction operator/ (const fraction& ) const;

    fraction operator+ (int ) const;
    fraction operator- (int ) const;
    fraction operator- () const;
    fraction operator* (int ) const;
    fraction operator/ (int ) const;

    friend fraction operator+ (int, const fraction& );
    friend fraction operator- (int, const fraction& );
    friend fraction operator* (int, const fraction& );
    friend fraction operator/ (int, const fraction& );

    fraction & operator+= (const fraction& );
    fraction & operator-= (const fraction& );
    fraction & operator*= (const fraction& );
    fraction & operator/= (const fraction& );

    fraction & operator+= (int );
    fraction & operator-= (int );
    fraction & operator*= (int );
    fraction & operator/= (int );

    int compare(const fraction& ) const;
    bool operator== (const fraction& ) const;
    bool operator!= (const fraction& ) const;
    bool operator>  (const fraction& ) const;
    bool operator<  (const fraction& ) const;
    bool operator>= (const fraction& ) const;
    bool operator<= (const fraction& ) const;

    bool operator== (int) const;
    bool operator== (double) const;
    bool operator!= (int) const;
    bool operator>  (int) const;
    bool operator<  (int) const;
    bool operator>= (int) const;
    bool operator<= (int) const;

    operator double() const;
    
    friend istream& operator>> (istream&, fraction&);
    friend ostream& operator<< (ostream&, const fraction&);

    friend std::string to_string(const fraction & f);

    static fraction get_decimal_from_str(const std::string &, size_t * idx = nullptr);
    static fraction construct_from_str(const std::string &, size_t * idx = nullptr);
    
    fraction();
    fraction(int );
    fraction(int ,int );
    fraction(const char* );
    fraction(const std::string &);
};

#endif