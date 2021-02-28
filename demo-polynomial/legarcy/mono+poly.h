#ifndef _MONO_POLY_H_
#define _MONO_POLY_H_

//mono+poly 2.0: support non-int expo and limitless terms
//class "Polynomial" is integrated with a "Monomial" container

#include <iostream>
#include <string.h>
#include <cmath>
#include <stdlib.h>
#include "fraction.h"

using namespace std;

class Monomial
{
public:
    fraction coef;
    fraction expo;
    //char letter;

    void print();
    //void set_letter();

    void multiply(Monomial& );
    void divide(Monomial& );
    double value(double );

    Monomial operator*(Monomial& );

    Monomial();
    Monomial(int, int);
    Monomial(fraction&, int );
    Monomial(int, fraction& );
    Monomial(fraction&, fraction& );
    Monomial(const char*, const char* );
};
void Monomial::multiply(Monomial& t)
{
    coef.multiply(t.coef);
    expo.add(t.expo);
}
void Monomial::divide(Monomial& t)
{
    coef.divide(t.coef);
    expo.subtract(t.expo);
}
double Monomial::value(double x)
{
    return coef.value()*pow(x,expo.value());
}
Monomial Monomial::operator*(Monomial& t)
{
    Monomial tmp(coef,expo);
    tmp.multiply(t);
    return tmp;
}
void Monomial::print()
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
        if (!expo.is_int() || expo < 0)
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
Monomial::Monomial(): coef(0),expo(0) {}

Monomial::Monomial(int a, int b): coef(a), expo(b){}
Monomial::Monomial(fraction& a, int b):coef(a), expo(b){}
Monomial::Monomial(int a, fraction& b):coef(a), expo(b){}

Monomial::Monomial(fraction& a, fraction& b ): coef(a), expo(b) {}
//Monomial::Monomial(fraction& a, fraction& b, char c = 'x'): letter(c), coef(a), expo(b) {}
Monomial::Monomial(const char* a, const char* b): coef(a), expo(b) {}

/*
class term
{
    Monomial k;
    term* previous;
    term* next;
    term():k(0,0){};
};*/

class Polynomial
{
private:
    int num;
    //term* ptr;
    Monomial** data;
public:
    void push(Monomial& );
    void modify(Monomial& );
    void add(Polynomial& );
    void subtract(Polynomial& );
    void add(Monomial& );
    void subtract(Monomial& );
    void multiply(Monomial& );
    void multiply(Polynomial& );
    void derivate();

    void copy(Polynomial& );
    void clear();
    double value(double );

    void print();
    void operator= (Polynomial& );

    Polynomial();
    Polynomial(Polynomial& );
    ~Polynomial();
};
void Polynomial::push(Monomial& n) //add_to_coef
{
    if (num == 0)
    {
        data = new Monomial*[num+1];
        data[num] = new Monomial;
        *data[num] = n;
        num++;
        return ;
    }
    //check for terms that already exist
    for(int i = 0; i < num; i++)
    {
        if (n.expo == data[i]->expo) 
        {
            data[i]->coef += n.coef;
            if (data[i]->coef == 0) 
            {
                delete data[i];
                Monomial** tdata;
                if(num - 1 > 0) {
                    tdata = new Monomial*[num-1];
                    int k = 0, j = 0;
                    while(j < num)
                    {
                        if(j == i) {j++; continue;}
                        tdata[k++] = data[j++];
                    }
                }
                else 
                { 
                    tdata = NULL;
                }
                delete []data;
                num--;
                data = tdata;
            }
            return;
        }
    }
    //add a new term
    Monomial** tdata = new Monomial*[num+1];
    int k = 0, i = 0;
    while (i < num && data[i]->expo > n.expo) tdata[k++] = data[i++];
    tdata[k] = new Monomial;
    *tdata[k++] = n;
    while (i < num) tdata[k++] = data[i++];
    delete []data;
    data = tdata;
    num++;
    return ;
}
void Polynomial::modify(Monomial& n)
{
    for (int i = 0; i < num; i++)
    {
        if (n.expo == data[i]->expo) 
        {
            data[i]->coef = n.coef;
            return;
        }
    }
    push(n);
}
void Polynomial::add(Polynomial& n)
{
    for (int i = 0; i < n.num; i++)
    {
        push(*n.data[i]);
    }
}
void Polynomial::add(Monomial& n)
{
    push(n);
}

void Polynomial::subtract(Polynomial& n)
{
    Monomial t;
    for (int i = 0; i < n.num; i++)
    {
        t = *n.data[i];
        t.coef = 0 - t.coef;
        push(t);
    }
}
void Polynomial::subtract(Monomial& n)
{
    Monomial t(n);
    t.coef = 0 - t.coef;
    push(t);
}
void Polynomial::copy(Polynomial& n)
{
    /*
    for (int i = 0; i< num;i++)
    {
        delete data[i];
    }
    delete []data;*/
    if(n.data == NULL) {
        clear();
        return ; 
    }
    clear();
    num = n.num;
    data = new Monomial*[n.num];
    for (int i = 0; i< n.num;i++)
    {
        data[i] = new Monomial;
        *data[i] = *n.data[i];
    }
    return;
}
void Polynomial::operator= (Polynomial& n)
{
    copy(n);
}
void Polynomial::multiply(Polynomial& n)
{
    Polynomial tmp;
    Monomial t;
    for (int i = 0; i< num; i++)
    {
        for (int j = 0; j < n.num; j++)
        {
            t = (*data[i]) * (*n.data[j]);
            tmp.push(t);
        }
    }
    copy(tmp);
}
void Polynomial::multiply(Monomial& n)
{
    Polynomial tmp;
    Monomial t;
    for (int i = 0; i < num; i++)
    {
        t = (*data[i]) * n;
        tmp.push(t);
    }
    copy(tmp);
}
void Polynomial::derivate()
{
    for (int i = 0; i < num; i++)
    {
        data[i]->coef *= data[i]->expo;
        data[i]->expo -= 1;
    }
}
void Polynomial::print()
{
    bool flag = false;
    for (int i = 0; i < num; i++)
    {
        if (flag && data[i]->coef.value() > 0) cout << " + ";
        data[i]->print();
        flag = true;
    }
}
void Polynomial::clear()
{
    if(data == NULL)
    {
        num = 0;
        return;
    }
    for (int i = 0; i < num; i++)
    {
        delete data[i];
    }
    delete []data;
    num = 0;
    data = NULL;
}
double Polynomial::value(double x)
{
    double t = 0;
    for (int i = 0; i < num; i++)
    {
        t += data[i]->coef.value() * pow(x, data[i]->expo.value());
    }
    return t;
}
Polynomial::Polynomial()
{
    num = 0;
    data = NULL;
}
Polynomial::Polynomial(Polynomial& n)
{
    num = 0;
    data = NULL;
    if(n.data != NULL) copy(n);
}
Polynomial::~Polynomial()
{
    if(!data)
    {
        for (int i = 0; i< num;i++) delete data[i];
        delete []data;
    }
}

#endif