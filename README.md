# fraction-class-cpp

A C++ fraction class which may enable you to use fraction in you C++ program.

## Usage

You can use `#inclued "fraction.h"` in your code so that you can create a fraction and then use them like regular numbers:

```cpp
#include <iostream>
int main() {
    fration a, b(1,2), c(3,4);
    std::cin >> a;
    std::cout << a + b;
    c *= b;
    std::cout << c;
}
```

However, `fraction` is not header-only currently, which means you may need to **compile** `fraction.cpp` and your program in the first place, then **link** it against your program, and finally **execute** the executable file. 

```bash
g++ -c fraction.cpp
g++ -c demo.cpp
g++ -o main fraction.o demo.o
./main
```

or you can do the compiling & linking stuff in one command

```bash
g++ fraction.cpp demo.cpp -o main
./main
```

> Maybe one can spare the trouble by also including `fraction.cpp` in your code?

2020/8/10 update: Now it uses `std::string` to receive user's keyboard input and process with relative functions.