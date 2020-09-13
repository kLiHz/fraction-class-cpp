#include <iostream>
#include "monomial.h"
#include "polynomial.h"
using namespace std;
/*int main()
{
    fraction a("1/2");
    monomial m1(a, 2), m2(a, 0);
    polynomial t1;
    t1.push(m1);
    cout << "t1: "; t1.print(); cout << endl;
    t1.push(m2);
    cout << "t1: "; t1.print(); cout << endl;
    t1.multiply(t1);
    cout << "t1: "; t1.print(); cout << endl;
    t1.multiply(m1);
    cout << "t1: "; t1.print(); cout << endl;
}*/
int main()
{
    fraction a(1, 3), b(1, 3);
    monomial m1(b, a);
    monomial m2("3/5", "2.5");
    polynomial t1;

    cout << "m1: "; m1.print(); cout << endl;
    cout << "m2: "; m2.print(); cout << endl;

    t1.push(m1);
    t1.push(m2);
    t1.print(); cout << endl;

    m1.multiply(m2);
    cout << "m1: "; m1.print(); cout << endl;
    cout << "m2: "; m2.print(); cout << endl;
    t1.push(m1);
    t1.push(m2);
    cout << "t1: "; t1.print(); cout << endl;

    monomial m3(24, 0);
    cout << "m3: "; m3.print(); cout << endl;

    t1.add(m3);
    cout << "t1: "; t1.print(); cout << endl;

    polynomial t2(t1);
    polynomial t3 = t1;

    t2.multiply(t1);

    t1.subtract(m3);

    t3.multiply(t1);

    cout << "t1: "; t1.print(); cout << endl;
    cout << "t2: "; t2.print(); cout << endl;
    cout << "t3: "; t3.print(); cout << endl;
    return 0;
}