#include <iostream>
//#include "legarcy/mono+poly.h" //poly2.0
#include "monomial.h"
#include "polynomial.h"
using namespace std;

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

polynomial poly_a, poly_b;
polynomial* now_opreate = &poly_a;
char now_opr = 'A';

void trim(char* strIn, char* strOut) // support in-place opreation
{
    char* a = strIn, * b;
    while (*a == ' ' || *a == '\n' || *a == '\t') a++; // ignore spaces at the beginning
    b = strIn + strlen(strIn) - 1; // get pointer pointing at the end of the line
    while (*b == ' ' || *b == '\n' || *a == '\t') b--; // ignore spaces at the end
    while (a <= b) *strOut++ = *a++; // transplace
    *strOut = '\0';
}

int Getline(char* dstStr)
{
    char c;
    int k = 0;
    scanf("%c", &c);
    while (c != '\n')
    {
        *dstStr++ = c;
        k++;
        scanf("%c", &c);
    }
    *dstStr = '\0';
    return k;
}

void guide(char choice)
{
    char usr_input[100];
    fraction t_coef = 0;
    fraction t_expo = 0;
    double x;
    monomial t_mono;
    polynomial tmp(poly_a);

    switch (choice)
    {
    case 's':
        cout << "Choose which poly. to operate on (A/B) > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
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
        Getline(usr_input);
        trim(usr_input, usr_input);
        t_coef = fraction(usr_input);

        cout << "指数 > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        t_expo = fraction(usr_input);

        t_mono = monomial(t_coef, t_expo);
        now_opreate->modify(t_mono);
        cout << "Poly now becomes: ";
        now_opreate->print();
        cout << endl;
        break;

    case 't':
        cout << "系数 > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        t_coef = fraction(usr_input);

        cout << "指数 > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        t_expo = fraction(usr_input);

        t_mono = monomial(t_coef, t_expo);
        now_opreate->push(t_mono);
        cout << "Poly now becomes: ";
        now_opreate->print();
        cout << endl;
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
        now_opreate->print();
        cout << endl;
        break;

    case 'a':
        cout << "Poly_A: "; poly_a.print(); cout << endl;
        cout << "Poly_B: "; poly_b.print(); cout << endl;
        break;

    case 'e':
        cout << "Enter the value of x: > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        x = atof(usr_input);
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
        tmp.print();
        cout << endl;
        break;

    case '+':
        tmp.add(poly_b);
        tmp.print();
        cout << endl;
        break;

    case '-':
        tmp.subtract(poly_b);
        tmp.print();
        cout << endl;
        break;

    case '*':
        tmp.multiply(poly_b);
        tmp.print();
        cout << endl;
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
    char choice[100];
    choice[0] = 'h';
    while (choice[0] != 'q')
    {
        guide(choice[0]);
        cout << "> ";
        Getline(choice);
        trim(choice, choice);
    }
    return 0;
}
