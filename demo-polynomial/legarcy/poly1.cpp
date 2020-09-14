#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <string.h> 
#include <stdlib.h>
using namespace std;
//poly 1.0 

class Polynomial //仅支持一元多项式，且无分数、负数指数幂
{
private:
    double coefs[30];
public:
    //系数coefficient 指数exponent 
    void assign_coef(double, int);
    void add_to_coef(double, int);
    void derivate();
    void add(Polynomial&);
    void substract(Polynomial&); //从当前多项式中减去
    int multiply(Polynomial&); //将当前多项式乘以
    long double value(double);
    void str_set(char*);

    void print();
    void output_term(int );
    void output_term(double , int );
    void set_to(const Polynomial&);
    void clear();

    Polynomial();
    Polynomial(double*);
};

void Polynomial::assign_coef(double coef, int expo) //重新指定系数
{
    if (expo < 0) {
        cout << "# The exponent needs to be a natural number!\n";
        cout << "# Failed to assign one term as: '";
        output_term(coef, expo);
        cout << "'. \n";
        return;
    }
    if (expo > 29) {
        cout << "# The exponent is too big!\n";
        cout << "# Failed to assign one term as: '";
        output_term(coef, expo);
        cout << "'. \n";
        return;
    }
    coefs[expo] = coef;
}
void Polynomial::output_term(int expo)
{
    if (coefs[expo] == 0) return;

    if (coefs[expo] < 0)  cout << " - ";
    if (coefs[expo] != 1 && coefs[expo] != -1) cout << abs(coefs[expo]);

    if (expo == 1) cout << "x";
    else cout << "x^" << expo;
}
void Polynomial::output_term(double coef, int expo)
{
    if (coef == 0) return;

    if (coef < 0)  cout << " - ";
    if (coef != 1 && coef != -1) cout << abs(coef);

    if (expo == 1) cout << "x";
    else cout << "x^" << expo;
}
void Polynomial::add_to_coef(double coef, int expo) //给某一项系数加上一定的值
{
    if (expo < 0) {
        cout << "# The exponent needs to be a natural number!\n";
        cout << "# Failed to add term: '";
        output_term(coef, expo);
        cout << "'. \n";
        return;
    }
    if (expo > 29) {
        cout << "# The exponent is too big!\n";
        cout << "# Failed to add term: '";
        output_term(coef, expo);
        cout << "'. \n";
        return;
    }
    coefs[expo] += coef;
}
void Polynomial::add(Polynomial& n)
{
    for (int i = 0; i < 30; i++)
    {
        //add_to_coef(addend.coefs[i], i); 
        coefs[i] += n.coefs[i];
    }
}
void Polynomial::substract(Polynomial& n) //从当前多项式中减去
{
    for (int i = 0; i < 30; i++)
    {
        coefs[i] -= n.coefs[i];
    }
}
int Polynomial::multiply(Polynomial& n)
{
    Polynomial temp;
    for (int i = 0; i < 30; i++)
    {
        if (coefs[i] == 0) continue;
        for (int j = 0; j < 30; j++)
        {
            if (n.coefs[j] == 0) continue;
            if (i + j > 29)
            {
                cout << "# Excessive exponent encountered! \n";
                cout << "# Try a polynomial with smaller exponents. \n";
                return 0;
            }
            temp.add_to_coef(coefs[i] * n.coefs[j], i + j);
        }
    }
    set_to(temp);
    return 1;
}
void Polynomial::derivate()
{
    for (int i = 1; i < 30; i++)
    {
        coefs[i - 1] = coefs[i] * i;
    }
}
long double Polynomial::value(double x)
{
    long double value = 0;
    for (int i = 0; i < 30; i++)
    {
        value += coefs[i] * pow(x, i);
    }
    return value;
}
void Polynomial::str_set(char* p)
{
    while (*p != '\0')
    {
        bool  if_negative;
        if (*p == '-') 
        {
            if_negative = true;
            p++;
        }
        else if_negative = false;
        if (*p == '+') p++;

        while (*p == ' ')p++;

        double t_coef = 0;
        bool if_x = false; //该项是否含x
        if (*p == 'x') {
            t_coef = 1;
            if_x = true;
        }
        else t_coef = atof(p);
        if (if_negative) t_coef = -t_coef;

        while (*p != '\0' && (*p != '^' && *p != '+' && *p != '-')) 
        {
            if (*p == 'x') if_x = true;
            p++;
        }

        int t_expo = 0;

        if (*p == '^') 
        {
            p++;
            t_expo = atoi(p);
            add_to_coef(t_coef, t_expo);
            while (*p != '\0' && *p != '+' && *p != '-') p++;
        }
        else if (*p == '+' || *p == '-' || *p == '\0') //说明这一项已经没有了
        {
            if (if_x) t_expo = 1;
            else t_expo = 0;
            add_to_coef(t_coef, t_expo);
        }
    }
}
void Polynomial::print()
{
    int i = 29;
    bool flag = 0; //记录是否至少输出了一项

    while (coefs[i] == 0 && i > 0) i--;

    if (i != 0) //单独输出最高次项
    {
        if (coefs[i] < 0) cout << " - ";
        if (coefs[i] != 1 && coefs[i] != -1) cout << abs(coefs[i]);

        if (i == 1) cout << "x";
        else cout << "x^" << i;
        flag = 1;
        i--;
    }

    for (; i > 0; i--)
    {
        if (coefs[i] == 0) continue;
        flag = 1;

        if (coefs[i] > 0) cout << " + ";
        else cout << " - ";
        if (coefs[i] != 1 && coefs[i] != -1) cout << abs(coefs[i]);

        if (i == 1) cout << "x";
        else cout << "x^" << i;
    }

    if (coefs[0] == 0) return;
    if (flag == 1 && coefs[0] > 0) cout << " + ";
    if (coefs[0] < 0) cout << " - ";
    cout << abs(coefs[0]);

    //cout << endl;
    return;
}
void Polynomial::set_to(const Polynomial& n)
{
    for (int i = 0; i < 30; i++) coefs[i] = n.coefs[i];
}
void Polynomial::clear()
{
    for (int i = 0; i < 30; i++) coefs[i] = 0;
}

Polynomial::Polynomial()
{
    clear();
}
Polynomial::Polynomial(double* n_coefs)
{
    for (int i = 0; i < 30; i++) coefs[i] = n_coefs[i];
}
void command_promption()
{
    cout << "---------------The Commands--------------- \n";
    cout << "s - 设置当前操作的多项式（A或B） \n";
    cout << "l - 调用assign_coef函数 \n";
    cout << "t - 调用add_to_coef函数 \n";
    cout << "i - 直接输入多项式，每项格式如 -2.3x^3 \n";
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
    double t_coef = 0;
    int t_expo = 0;
    double x;
    Polynomial tmp(poly_a);
    bool m_flag;

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
        cout << "Input the coef. > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        t_coef = atof(usr_input);

        cout << "Input the expo. > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        t_expo = atoi(usr_input);

        now_opreate->assign_coef(t_coef, t_expo);
        cout << "Poly now becomes: ";
        now_opreate->print();
        cout << endl;
        break;

    case 't':
        cout << "Input the coef. > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        t_coef = atof(usr_input);

        cout << "Input the expo. > ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        t_expo = atoi(usr_input);

        now_opreate->add_to_coef(t_coef, t_expo);
        cout << "Poly now becomes: ";
        now_opreate->print();
        cout << endl;
        break;

    case 'i':
        cout << "> ";
        Getline(usr_input);
        trim(usr_input, usr_input);
        now_opreate->clear();
        now_opreate->str_set(usr_input);
        now_opreate->print();
        cout << endl;
        break;

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
            tmp.set_to(poly_a);
        }
        if (now_opr == 'B') {
            tmp.set_to(poly_b);
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
        tmp.substract(poly_b);
        tmp.print();
        cout << endl;
        break;

    case '*':
        m_flag = tmp.multiply(poly_b);
        if (m_flag) tmp.print();
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

