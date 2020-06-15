#include "fraction.h"

int fraction::gcd(int x,int y)
{
	int t;
	while (y!=0)
	{
		t=x%y;
		x=y;
		y=t;
	}
	return x;
}
int fraction::lcm(int a, int b)
{
	//return a*b/gcd(a,b);
    //if (a % b == 0) return a;
    //if (b % a == 0) return b;
    int t_gcd = gcd(a,b);
    if (a % t_gcd == 0) a /= t_gcd;
    else if (b % t_gcd == 0) b /= t_gcd;
    return a * b;
}

istream& operator>> (istream& is, fraction& f)
{
    char input[100];
    is >> input;
    f = fraction(input);
    return is;
}
ostream& operator<< (ostream& os, const fraction& f)
{
    int tA = abs(f.A);
    if (f.A < 0) os << " - ";
    if (tA >= f.B && tA % f.B == 0) os << (tA / f.B);
    else if (tA == 0) os << 0;
    else os << tA << "/" << f.B;
    return os;
}
void fraction::add(const fraction& addend)
{
    if (B == addend.B) {
        A += addend.A;
        return;
    }
    else if (addend.B == 1) {
        A += (addend.A * B);
    }
    else {
        int t = lcm(B, addend.B);
        int m1 = t / B;
        int m2 = t / addend.B;
        A *= m1;
        B *= m1;
        A += (addend.A * m2);
        reduce();
    }
}
void fraction::add(int n)
{
    A += n*B;
}
void fraction::subtract(const fraction& subtrahend)
{
    if (B == subtrahend.B) {
        A -= subtrahend.A;
        return;
    }
    else if (subtrahend.B == 1) {
        A -= (subtrahend.A * B);
    }
    else {
        int t = lcm(B, subtrahend.B);
        int m1 = t / B;
        int m2 = t / subtrahend.B;
        A *= m1;
        B *= m1;
        A -= (subtrahend.A * m2);
        reduce();
    }
}
void fraction::multiply(const fraction& multiplier)
{
    int d1 = 1, d2 = 1;
    if (A != 0) d1 = gcd(A, multiplier.B);
    if (multiplier.A != 0) d2 = gcd(multiplier.A, B);
    A /= d1;
    B /= d2;
    A *= (multiplier.A / d2);
    B *= (multiplier.B / d1);
    //reduce();
}
void fraction::divide(const fraction& divisor)
{
    if (divisor.A == 0) {cout << "cannot divided by 0!\n"; return;}\
    int d1 = 1, d2 = 1;
    d1 = gcd(B,divisor.B);
    if (A != 0 && divisor.A != 0) d2 = gcd(A,divisor.A);
    A /= d2;
    B /= d1;
    A *= (divisor.B / d1);
    B *= (divisor.A / d2);
    //reduce();
}
void fraction::reduce()
{
    bool if_negative = false;
    if ((A < 0 && B > 0) || (A > 0 && B < 0)) //if (A * B < 0)
    {
        if_negative = true;
    }
    A = abs(A);
    B = abs(B);
    int d = gcd(A,B);
    A /= d;
    B /= d;
    if (if_negative) A = -A;
}
void fraction::print()
{
    int tA = abs(A);
    if (A < 0) cout << " - ";
    if (tA >= B && tA % B == 0) cout << (tA/B);
    else if (tA == 0) cout<<0;
    else cout << tA << "/" << B;
}
bool fraction::if_int() const
{
    int tA = abs(A);
    if ((tA >= B && tA % B == 0)|| tA == 0) return true;
    else return false;
}
double fraction::value() const
{
    return (double) A / B;
}

fraction fraction::operator+ (const fraction& addend)
{
    fraction t(A,B);
    t.add(addend);
    return t;
}
fraction fraction::operator- (const fraction& subtrahend)
{
    fraction t(A,B);
    t.subtract(subtrahend);
    return t;
}
fraction fraction::operator* (const fraction& multiplier)
{
    fraction t(A,B);
    t.multiply(multiplier);
    return t;
}
fraction fraction::operator/ (const fraction& divisor)
{
    fraction t(A,B);
    t.divide(divisor);
    return t;
}

fraction fraction::operator+ (int num )
{
    fraction addend(num);
    fraction t(A,B);
    t.add(addend);
    return t;
}
fraction fraction::operator- (int num )
{
    fraction subtrahend(num);
    fraction t(A,B);
    t.subtract(subtrahend);
    return t;
}
fraction fraction::operator* (int num )
{
    fraction multiplier(num);
    fraction t(A,B);
    t.multiply(multiplier);
    return t;
}
fraction fraction::operator/ (int num )
{
    fraction divisor(num);
    fraction t(A,B);
    t.divide(divisor);
    return t;
}

fraction operator+ (int num, const fraction& t)
{
    fraction p(num);
    p.add(t);
    return p;
}
fraction operator- (int num, const fraction& t)
{
    fraction p(num);
    p.subtract(t);
    return p;
}
fraction operator* (int num, const fraction& t)
{
    fraction p(num);
    p.multiply(t);
    return p;
}
fraction operator/ (int num, const fraction& t)
{
    fraction p(num);
    p.divide(t);
    return p;
}

void fraction::operator+= (const fraction& addend)
{
    add(addend);
}
void fraction::operator-= (const fraction& subtrahend)
{
    subtract(subtrahend);
}
void fraction::operator*= (const fraction& multiplier)
{
    multiply(multiplier);
}
void fraction::operator/= (const fraction& divisor)
{
    divide(divisor);
}

void fraction::operator+= (int num)
{
    fraction t(num);
    add(t);
}
void fraction::operator-= (int num)
{
    fraction t(num);
    subtract(t);
}
void fraction::operator*= (int num)
{
    fraction t(num);
    multiply(t);
}
void fraction::operator/= (int num)
{
    fraction t(num);
    divide(t);
}

int fraction::compare(const fraction& t)
{
    /*
    fraction a(A,B), b;
    b = t;
    if (a.A * b.A < 0)
    {
        if (a.A < 0) return -1;
        if (b.A < 0) return 1;
    }
    if (a.B != b.B) 
    {
        a.A *= t.B;
        a.B *= t.B;
        b.A *= B;
        b.B *= B;
    }
    if (a.A < b.A) return -1;
    else if (a.A == b.A) return 0;
    //if (a.A > b.A) 
    else return 1;
    */
    if (A * t.A < 0)
    {
        if (A < 0) return -1;
        if (t.A < 0) return 1;
    }
    if (A * t.B < t.A * B) return -1;
    else if (A * t.B == t.A * B) return 0;
    else return 1;
}
bool fraction::operator== (const fraction& t)
{
    return A * t.B == t.A * B;
    //return (A == t.A && B == t.B);
}
bool fraction::operator== (int t)
{
    return A == t * B;
}
bool fraction::operator!= (const fraction& t)
{
    return A * t.B != t.A * B;
}
bool fraction::operator> (const fraction& t)
{
    if (compare(t) == 1) return true;
    else return false;
}
bool fraction::operator< (const fraction& t)
{
    if (compare(t) == -1) return true;
    else return false;
}
bool fraction::operator>= (const fraction& t)
{
    if(compare(t) != -1) return true;
    else return false;
}
bool fraction::operator<= (const fraction& t)
{
    if(compare(t) != 1) return true;
    else return false;
}
bool fraction::operator== (double t)
{
    return value() == t;
}
bool fraction::operator!= (int num)
{
    return A != num * B;
}
bool fraction::operator> (int num)
{
    return A > num * B;
}
bool fraction::operator< (int num)
{
    return A < num * B;
}
bool fraction::operator>= (int num)
{
    return A >= num * B;
}
bool fraction::operator<= (int num)
{
    return A <= num * B;
}

fraction::fraction(): A(0), B(1) {}
fraction::fraction(int a): A(a), B(1) {}
fraction::fraction(int a, int b)
{
    if (b == 0) {cout<<"No 0 as denominator!\n"; b = 1;}
    A = a;
    B = b;
    reduce();
}
fraction::fraction(const char* str)
{
    A = 0; B = 1;
    char* sep = (char* )str;
    char* dpoint = (char* )str;
    while (*sep != '/' && *sep != '\0') sep++;
    if (*sep == '\0') //未找到分数线
    {
        while (*dpoint != '.'&&*dpoint != '\0') dpoint++;
        if(*dpoint == '\0') //没有小数点，即为一个整数
        {
            add( atoi(str) );
        }
        else 
        {
            int t1 = atoi(str);
            dpoint++;
            int t2 = atoi(dpoint);
            if (t1 < 0) t2 = -t2;
            int t3 = 1;
            while( *dpoint >= '0' && *dpoint <= '9') {t3*=10; dpoint++;}
            A = t2;
            //if (t1 < 0) A = -A;
            B = t3;
            reduce();
            add(t1);
        }
    }
    else //存在分数线
    {
        //处理分数线之前的部分，存入当前类
        while (*dpoint != '.' && *dpoint != '/') dpoint++;
        if(*dpoint == '/') //没有小数点，即为一个整数
        {
            add( atoi(str) );
        }
        else 
        {
            int t1 = atoi(str);
            dpoint++;
            int t2 = atoi(dpoint);
            if (t1 < 0) t2 = -t2;
            int t3 = 1;
            while( *dpoint >= '0' && *dpoint <= '9') {t3*=10; dpoint++;}
            A = t2;
            B = t3;
            reduce();
            add(t1);
        }
        //处理分数线之后的部分，
        fraction div;
        dpoint = sep;
        while (*dpoint != '.'&&*dpoint != '\0') dpoint++;
        if(*dpoint == '\0') //没有小数点，即为一个整数
        {
            div.add( atoi(sep+1) );
        }
        else 
        {
            int t1 = atoi(sep+1);
            dpoint++;
            int t2 = atoi(dpoint);
            if (t1 < 0) t2 = -t2; 
            int t3 = 1; //10^n
            while( *dpoint >= '0' && *dpoint <= '9') {t3*=10; dpoint++;}
            div.A = t2;
            div.B = t3;
            div.reduce();
            div.add(t1);
        }
        divide(div);
    }
}