# A Fraction Class in C++

A C++ fraction class which may enable you to use fraction in you C++ program.

## Usage

**New:** `fraction` class is now header-only, just `#inclued "fraction.hpp"`. Then, you can create a fraction and then use them like regular numbers.

```cpp
#include <iostream>
#include "fraction.hpp"

int main() {
    using frac = fraction<int>;

    std::cout << frac("1/3") + frac(1,4) * frac(1,2);

    frac a, b(1,2), c("3/4");

    std::cin >> a;
    std::cout << a + b;
    std::cout << c * b;
}
```

For more demonstration, please refer to [demo.cpp](./demo.cpp).

**Legacy:** In this way, you may need to **compile** `fraction.cpp` and your program in the first place, then **link** it against your program, and finally **execute** the executable file. 

You can use `#inclued "fraction.h"` in your code:

```cpp
#include <iostream>
#inclued "fraction.h"

int main() {
    fration a, b(1,2), c(3,4);
    std::cin >> a;
    std::cout << a + b;
    c *= b;
    std::cout << c;
}
```

Then you may compile and link manually in terminal.

```bash
g++ -c fraction.cpp
g++ -c demo.cpp
g++ -o main fraction.o demo.o
./main
```

or you may do the compiling & linking stuff in one command:

```bash
g++ fraction.cpp demo.cpp -o main
./main
```

## Log

2020/08/10 update: Now it uses `std::string` to receive user's keyboard input and process with relative functions.

2021/03/19 update: Now `fraction` is a template class and header-only.

## Other Fraction Class Repos on GitHub

- https://github.com/Anmol-Singh-Jaggi/Fraction-Library/blob/master/fraction.cpp
- https://github.com/featdd/FractionClass
- https://github.com/avivaprins/Fraction
