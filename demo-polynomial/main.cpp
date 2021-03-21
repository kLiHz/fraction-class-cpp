#include <iostream>
#include <string>
//#include "legarcy/mono+poly.h" //poly2.0
#include "monomial.h"
#include "polynomial.h"

using std::cin; 
using std::cout;
using std::endl;

void command_promption()
{
    cout << "---------------The Commands--------------- \n";
    cout << "s - 设置当前操作的多项式（A或B） \n";
    cout << "l - 调用assign_coef函数 \n";
    cout << "t - 调用add_to_coef函数 \n";
    //cout << "i - 直接输入多项式，每项格式如 -2.3x^3 \n";
    cout << "c - 调用clear函数 \n";
    cout << "v - 显示当前多项式 \n";
    cout << "a - 显示所有多项式 \n";
    cout << "d - 对当前多项式求导并显示 \n";
    cout << "e - 计算当前多项式的值 \n";
    cout << "+ - 显示A+B的和 \n";
    cout << "- - 显示A-B的差 \n";
    cout << "* - 显示A*B的积 \n";
    cout << "h - help \n";
    cout << "q - quit \n";
    cout << "------------------------------------------ \n";
}

Polynomial poly_a, poly_b;
Polynomial* now_opreate = &poly_a;
char now_opr = 'A';

void guide(char choice)
{
    std::string usr_input, s_coef, s_expo;
#ifdef _FRACTION_H_
    fraction t_coef = 0;
    fraction t_expo = 0;
#else
    double t_coef = 0;
    double t_expo = 0;
#endif
    double x;
    Polynomial tmp(poly_a);

    switch (choice)
    {
    case 's':
        cout << "Choose which poly. to operate on (A/B) > ";
        getline(cin,usr_input);
        if (usr_input[0] == 'A' || usr_input[0] == 'a')
        {
            now_opreate = &poly_a;
            cout << "Polynomial A is now chosen!\n";
            now_opr = 'A';
        }
        else if (usr_input[0] == 'B' || usr_input[0] == 'b')
        {
            now_opreate = &poly_b;
            cout << "Polynomial B is now chosen!\n";
            now_opr = 'B';
        }
        else cout << "Polynomial under opreation is " << now_opr << ".\n";
        break;

    case 'l':
        cout << "系数 > ";
        getline(cin, s_coef);
        cout << "指数 > ";
        getline(cin, s_expo);

#ifdef _FRACTION_HPP_
        t_coef = frac(s_coef);
        t_expo = frac(s_expo);
#else
        t_coef = stod(s_coef);
        t_expo = stod(s_expo);
#endif
        now_opreate->modify_term_as(Monomial(t_coef, t_expo));
        cout << "Poly now becomes: " << *now_opreate << endl;
        break;

    case 't':
        cout << "系数 > ";
        getline(cin, s_coef);
        cout << "指数 > ";
        getline(cin, s_expo);

#ifdef _FRACTION_HPP_
        t_coef = frac(s_coef);
        t_expo = frac(s_expo);
#else
        t_coef = stod(s_coef);
        t_expo = stod(s_expo);
#endif
        now_opreate->push(Monomial(t_coef, t_expo));
        cout << "Poly now becomes: " << *now_opreate << endl;
        break;
/*
    case 'i':
        cout << "> ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        now_opreate->clear();
        now_opreate->str_set(usr_input);
        now_opreate->print();
        cout << endl;
        break;
*/
    case 'c':
        now_opreate->clear();
        cout << "Poly_" << now_opr << " has been cleared!" << endl;
        break;

    case 'v':
        cout << *now_opreate << endl;
        break;

    case 'a':
        cout << "Poly_A: " << poly_a << endl;
        cout << "Poly_B: " << poly_b << endl;
        break;

    case 'e':
        cout << "Enter the value of x: > ";
        getline(cin,usr_input);
        x = stoi(usr_input);
        cout << "Value: " << now_opreate->value(x) << endl;
        break;

    case 'd':
        if (now_opr == 'A') {
            tmp.copy(poly_a);
        }
        if (now_opr == 'B') {
            tmp.copy(poly_b);
        }
        tmp.derivate();
        cout << tmp << endl;
        break;

    case '+':
        tmp.add(poly_b);
        cout << tmp << endl;
        break;

    case '-':
        tmp.subtract(poly_b);
        cout << tmp << endl;
        break;

    case '*':
        tmp.multiply(poly_b);
        cout << tmp << endl;
        break;

    case 'q':
        break;

    case 'h': default:
        command_promption();
        break;
    }
    return;
}

int main()
{
    std::string choice = "h";
    //choice[0] = 'h';
    while (choice[0] != 'q')
    {
        guide(choice[0]);
        cout << "> ";
        getline(cin,choice);
    }
    return 0;
}
