#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <iostream>
#include <string.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

class fraction
{
private:
    int A;  //numerator
    int B;  //denominator
public:
    static int gcd(int, int);
    static int lcm(int, int);
    void reduce();
    void print();
    bool if_int() const;

    void add(const fraction& );
    void add(int );
    void subtract(const fraction& );
    void multiply(const fraction& );
    void divide(const fraction& );
    double value() const;

    fraction operator+ (const fraction& );
    fraction operator- (const fraction& );
    fraction operator* (const fraction& );
    fraction operator/ (const fraction& );

    fraction operator+ (int );
    fraction operator- (int );
    fraction operator* (int );
    fraction operator/ (int );

    friend fraction operator+ (int, const fraction& );
    friend fraction operator- (int, const fraction& );
    friend fraction operator* (int, const fraction& );
    friend fraction operator/ (int, const fraction& );

    void operator+= (const fraction& );
    void operator-= (const fraction& );
    void operator*= (const fraction& );
    void operator/= (const fraction& );

    void operator+= (int );
    void operator-= (int );
    void operator*= (int );
    void operator/= (int );

    int compare(const fraction& );
    bool operator== (const fraction& );
    bool operator!= (const fraction& );
    bool operator> (const fraction& );
    bool operator< (const fraction& );
    bool operator>= (const fraction& );
    bool operator<= (const fraction& );

    bool operator== (int);
    bool operator== (double );
    bool operator!= (int );
    bool operator> (int );
    bool operator< (int );
    bool operator>= (int );
    bool operator<= (int );

    friend istream& operator>> (istream&, fraction&);
    friend ostream& operator<< (ostream&, const fraction&);

    fraction();
    fraction(int );
    fraction(int ,int );
    fraction(const char* );
};

#endif