# fraction-class-cpp
A C++ fraction class which may enable you to use fraction in you C++ program.
# Usage
You can use `#inclued "fraction.h"` in youe code so that you can create a fraction class like:
```cpp
fration a, b(1,2), c(3,4);
```
and use them like:
```
std::cout << a + b;
c *= b;
std::cout << c;
```
However, you may need to compile `fraction.cpp` in the first place:
```
g++ -c fraction.cpp
```
and link it with your program:
```
g++ -c yourprogam.cpp
g++ -o main fraction.o yourprogram.o
```
and then execute the executable file.
```
./main
```
Well, you can spare the trouble by also including `fraction.cpp` in your code.
