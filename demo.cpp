#include <iostream>
#include "fraction.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    fraction m, n;
    cout << "What's the product of m and n?\n";
    cout << "Input m: ";
    cin >> m;
    cout << "Input n: ";
    cin >> n;
    cout << "The product of m and n is: " << m * n << endl;

    fraction a,b,c,d,e,f;
    std::string str = "1 / 2  3.4a.s.3.3 / 9.9  55/66  4.5/9 3";
    cout << "Extract 6 fractions from string: " << str << endl;
    std::size_t sz;
    a = fraction::construct_from_str(str, &sz);
    str = str.substr(sz);
    b = fraction::construct_from_str(str, &sz);
    str = str.substr(sz);
    c = fraction::construct_from_str(str, &sz);
    str = str.substr(sz);
    d = fraction::construct_from_str(str, &sz);
    str = str.substr(sz);
    e = fraction::construct_from_str(str, &sz);
    str = str.substr(sz);
    f = fraction::construct_from_str(str, &sz);
    cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << endl;
    
    return 0;
}

/*int main()
{
    fraction a(1, 3), b(1, 3), c(1, 3), d(1, 3);
    fraction t(1, 2);
    a.add(t);
    a.print();
    cout << endl;
    b.subtract(t);
    b.print();
    cout << endl;
    c.multiply(t);
    c.print();
    cout << endl;
    d.divide(t);
    d.print();
    cout << endl;
}*/