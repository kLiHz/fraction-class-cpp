#include <iostream>
#include <vector>

#include "fraction.hpp"

using std::cin;
using std::cout;

int main()
{
    using frac = fraction<long long>;

    frac m, n;
    cout << "What's the product of m and n?\n";
    cout << "Input m: ";
    cin >> m;
    cout << "Input n: ";
    cin >> n;
    cout << "The product of m and n is: " << m * n << "\n\n";

    // Construct from string

    std::vector<frac> fracs;
    std::string str = "1 / 2  3.4a.s.3.3 / 9.9  55/66  4.5/9 3";

    cout << "Extract 6 fractions from: \"" << str << "\" \n";
    std::size_t sz;
    for (int i = 0; i < 6; ++i) {
        fracs.push_back( frac::construct_from_str(str, &sz) );
        str = str.substr(sz);
    }

    for (auto f : fracs) cout << f << ' ';
    std::cout << "\n\n";
    
    // Construct from double

    double val;
    int precision;
    std::cout << "Value: ";
    std::cin >> val;
    std::cout << "Precision: ";
    std::cin >> precision;

    std::cout << "The fraction should be '" << frac(val, precision) << "'.\n";

    return 0;
}
