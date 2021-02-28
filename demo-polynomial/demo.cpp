#include <iostream>
#include "monomial.h"
#include "polynomial.h"

using std::cin; 
using std::cout;
using std::endl;

int main()
{
    fraction a(1, 3), b(1, 3);
    Monomial m1(b, a);
    Monomial m2("3/5", "2.5");
    Polynomial t1;

    cout << "m1: " << m1 << endl;
    cout << "m2: " << m2 << endl;

    t1.push(m1); cout << t1 << endl;
    t1.push(m2); cout << t1 << endl;

    m1.multiply(m2);
    cout << "m1: " << m1 << endl;
    cout << "m2: " << m2 << endl;
    t1.push(m1);
    t1.push(m2);
    cout << "t1: " << t1 << endl;

    Monomial m3(24, 0);
    cout << "m3: " << m3 << endl;

    t1.add(m3);
    cout << "t1: " << t1 << endl;

    Polynomial t2(t1);
    Polynomial t3 = t1;

    t2.multiply(t1);

    t1.subtract(m3);

    t3.multiply(t1);

    cout << "t1: " << t1 << endl;
    cout << "t2: " << t2 << endl;
    cout << "t3: " << t3 << endl;
    return 0;
}
