#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <string>
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
        //cout << "指数需为自然数!\n";
        cout << "# Failed to assign one term as: '";
        output_term(coef, expo);
        cout << "'. \n";
        return;
    }
    if (expo > 29) {
        cout << "# The exponent is too big!\n";
        //cout << "指数过大, 溢出!\n";
        cout << "# Failed to assign one term as: '";
        output_term(coef, expo);
        cout << "'. \n";
        return;
    }
    coefs[expo] = coef;
}

void Polynomial::output_term(double coef, int expo)
{
    if (coef == 0) return;

    if (coef < 0)  cout << " - ";
    if (coef != 1 && coef != -1) cout << abs(coef);

    if (expo == 1) cout << "x";
    else if (expo == 0) {}
    else cout << "x^" << expo;
}
void Polynomial::add_to_coef(double coef, int expo) //给某一项系数加上一定的值
{
    if (expo < 0) {
        cout << "# The exponent needs to be a natural number!\n";
        //cout << "指数需为自然数!\n";
        cout << "# Failed to add term: '";
        output_term(coef, expo);
        cout << "'. \n";
        return;
    }
    if (expo > 29) {
        cout << "# The exponent is too big!\n";
        //cout << "指数过大, 溢出!\n";
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
                //cout << "运算时指数溢出! \n";
                //cout << "请尝试包含项的次数较小的多项式. \n";
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
    bool flag = 0; //记录是否至少输出了一项

    for (int i = 29; i >= 0; i--)
    {
        if (coefs[i] == 0) continue;
        if (flag && coefs[i] > 0) cout << " + ";
        output_term(coefs[i],i);
        flag = 1;
    }
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

Polynomial polys[3];
Polynomial* now_opreate = &polys[0];

void guide(char choice)
{
    string usr_input;
    double t_coef = 0;
    int t_expo = 0;
    double x;
    Polynomial tmp(polys[0]);
    bool m_flag;

    switch (choice)
    {
    case 's':
        cout << "Choose which poly. to operate on (A, B or C) > ";
        getline(cin, usr_input);
        if (usr_input[0] >= 'a' && usr_input[0] <= 'c')
        {
            now_opreate = & polys[usr_input[0]-'a'];
            cout << "Polynomial " << char('A' + (now_opreate - polys)) << " is now chosen!\n";
        }
        else if (usr_input[0] >= 'A' && usr_input[0] <= 'C')
        {
            now_opreate = & polys[usr_input[0]-'A'];
            cout << "Polynomial " << char('A' + (now_opreate - polys)) << " is now chosen!\n";
        }
        else cout << "Polynomial under opreation is " << char('A' + (now_opreate - polys))  << ".\n";
        break;

    case 'l':
        cout << "Input the coef > ";
        getline(cin, usr_input);
        t_coef = stod(usr_input);

        cout << "Input the expo > ";
        getline(cin, usr_input);
        t_expo = stod(usr_input);

        now_opreate->assign_coef(t_coef, t_expo);
        cout << "Poly now becomes: ";
        now_opreate->print();
        cout << endl;
        break;

    case 't':
        cout << "Input the coef > ";
        getline(cin, usr_input);
        t_coef = stod(usr_input);

        cout << "Input the expo > ";
        getline(cin, usr_input);
        t_expo = stod(usr_input);

        now_opreate->add_to_coef(t_coef, t_expo);
        cout << "Poly now becomes: ";
        now_opreate->print();
        cout << endl;
        break;

    case 'c':
        now_opreate->clear();
        cout << "Poly: " << char('A' + (now_opreate - polys))  << " has been cleared!" << endl;
        break;

    case 'v':
        now_opreate->print();
        cout << endl;
        break;

    case 'a':
        cout << "A: "; polys[0].print(); cout << endl;
        cout << "B: "; polys[1].print(); cout << endl;
        cout << "C: "; polys[2].print(); cout << endl;
        break;

    case 'e':
        cout << "Enter the value of x > ";
        getline(cin, usr_input);
        x = stod(usr_input);
        cout << "Value: " << now_opreate->value(x) << endl;
        break;

    case 'd':
        tmp.set_to(*now_opreate);
        tmp.derivate();
        tmp.print();
        cout << endl;
        break;

    case '+':
        tmp.set_to(polys[0]);
        tmp.add(polys[1]);
        tmp.print();
        cout << endl;
        break;

    case '-':
        tmp.set_to(polys[0]);
        tmp.substract(polys[1]);
        tmp.print();
        cout << endl;
        break;

    case '*':
        tmp.set_to(polys[0]);
        m_flag = tmp.multiply(polys[1]);
        if (m_flag) tmp.print();
        cout << endl;
        break;

    case 'q':
        break;

    case 'h': 
        command_promption();
        break;
    default:
        cout<<"Invalid command!\n";
        command_promption();
        break;
    }
    return;
}
int main()
{
    string choice = "h";
    while (choice[0] != 'q')
    {
        guide(choice[0]);
        cout << "> ";
        getline(cin, choice);
    }
    return 0;
}