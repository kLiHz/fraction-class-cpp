# fraction-class-cpp
A C++ fraction class which may enable you to use fraction in you C++ program.
## Usage
You can use `#inclued "fraction.h"` in your code so that you can create a fraction like this:
```cpp
fration a, b(1,2), c(3,4);
```
and use them like:
```cpp
std::cin>>a;
std::cout << a + b;
c *= b;
std::cout << c;
```
However, you may need to compile `fraction.cpp` in the first place, **link** it with your program,  and then **execute** the executable file.

```bash
g++ -c fraction.cpp
g++ -c demo.cpp
g++ -o main fraction.o demo.o
./main
```


Maybe you can spare the trouble by also including `fraction.cpp` in your code?



2020/8/10 update: Now it uses `std::string` to receive user's keyboard input and process with relative functions.