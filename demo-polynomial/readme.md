# polynomial

This is one piece of our homework for OOP.

This program is aimed to perform some basic processing on polynomial (with only one unknown).

Now there are 3 versions of this program. 

`Poly1` is the most basic, which only support 30 terms whose exponents are from 0-29.  This version can be found in `legarcy`, which is a single file named `poly1.cpp`. 

`Poly2` is developed after `fraction` class is finished (or maybe in fact the `fraction` class is developed in order to improve `Poly1`). This version introduced the concept of `monomial` and `polynomial` and uses dynamic memory management, or maybe you can say the the `polynomial` class is a container of the `monomial` class. 

`Poly3` makes some changes compared to `Poly2`. The class `polynomial` uses `list<monomial>` to manage all of its terms instead of making itself a container.

Since the 2nd and 3rd versions' difference are about data structure and they share the same controlling interface, so you can change the file included in `main.cpp` to shift between these two version. (Currently, as for `Poly3`, you need to link three object file together, but there is no need to do this for `Poly2`)

