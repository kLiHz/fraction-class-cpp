# fraction-class-cpp
A C++ fraction class which may enable you to use fraction in you C++ program.
# Usage
You can use `#inclued "fraction.h"` in youe code so that you can create a fraction class like:
```cpp
fration a, b(1,2);
```
However you may need to compile `fraction.cpp` in the first place:
```
g++ -c fraction.cpp
g++ -c yourprogam.cpp
```
and link them
```
g++ -o main fraction.o yourprogram.o
```
and then execute the binary file.
```
./main
```
You can spare the trouble by also including `fraction.cpp` in your code.
