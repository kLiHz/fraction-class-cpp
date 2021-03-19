#include "fraction.h"

int fraction::gcd(int x, int y) 
{
    do {
        x %= y;
        std::swap(x, y);
    } while (y);
    return x;
}

int fraction::lcm(int a, int b)
{
    if (a == 0 || b == 0) return 0;
    a /= gcd(a,b);
    return a * b;
}

istream& operator>> (istream& is, fraction& f)
{
    //char input[100];
    std::string input;
    is >> input;
    f = fraction::construct_from_str(input);
    return is;
}

ostream& operator<< (ostream& os, const fraction& f)
{
    os << to_string(f);
    return os;
}

std::string to_string(const fraction & f) {
    std::string str;
    if ( f < 0 ) str += "-";
    if ( f.is_int() ) {
        str += std::to_string( int(abs(f.A) / f.B) );
    } else {
        str += std::to_string( f.A );
        str += "/";
        str += std::to_string( f.B );
    }
    return str;
}

fraction::operator double() const
{
    return value();
}

fraction & fraction::add(const fraction& addend)
{
    if (B == addend.B) {
        A += addend.A;
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
    return *this;
}
fraction & fraction::add(int n)
{
    A += n*B;
    return *this;
}
fraction & fraction::subtract(const fraction& subtrahend)
{
    if (B == subtrahend.B) {
        A -= subtrahend.A;
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
    return *this;
}
fraction & fraction::multiply(const fraction& multiplier)
{
    int d1 = 1, d2 = 1;
    if (A != 0) d1 = gcd(A, multiplier.B);
    if (multiplier.A != 0) d2 = gcd(multiplier.A, B);
    A /= d1;
    B /= d2;
    A *= (multiplier.A / d2);
    B *= (multiplier.B / d1);
    //reduce();
    return *this;
}
fraction & fraction::divide(const fraction& divisor)
{
    if (divisor.A == 0) { throw "cannot divided by 0!"; } // TODO
    int d1 = gcd(B, divisor.B);
    int d2 = (A != 0) ? gcd(A, divisor.A) : 1;
    A /= d2;
    B /= d1;
    A *= (divisor.B / d1);
    B *= (divisor.A / d2);
    //reduce();
    return *this;
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

bool fraction::is_int() const
{
    auto _A = abs(A);
    return _A == 0 || (_A >= B && _A % B == 0);
}

double fraction::value() const
{
    return (double) A / B;
}

fraction fraction::operator+ (const fraction& addend) const
{
    fraction t(A,B);
    t.add(addend);
    return t;
}
fraction fraction::operator- (const fraction& subtrahend) const
{
    fraction t(A,B);
    t.subtract(subtrahend);
    return t;
}
fraction fraction::operator* (const fraction& multiplier) const
{
    fraction t(A,B);
    t.multiply(multiplier);
    return t;
}
fraction fraction::operator/ (const fraction& divisor) const
{
    fraction t(A,B);
    t.divide(divisor);
    return t;
}

fraction fraction::operator+ (int num ) const
{
    fraction addend(num);
    fraction t(A,B);
    t.add(addend);
    return t;
}
fraction fraction::operator- (int num ) const
{
    fraction subtrahend(num);
    fraction t(A,B);
    t.subtract(subtrahend);
    return t;
}
fraction fraction::operator- () const
{
    return fraction(-A,B);
}
fraction fraction::operator* (int num ) const
{
    fraction multiplier(num);
    fraction t(A,B);
    t.multiply(multiplier);
    return t;
}
fraction fraction::operator/ (int num ) const
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

fraction & fraction::operator+= (const fraction& addend)
{
    add(addend);
    return *this;
}
fraction & fraction::operator-= (const fraction& subtrahend)
{
    subtract(subtrahend);
    return *this;
}
fraction & fraction::operator*= (const fraction& multiplier)
{
    multiply(multiplier);
    return *this;
}
fraction & fraction::operator/= (const fraction& divisor)
{
    divide(divisor);
    return *this;
}

fraction & fraction::operator+= (int num)
{
    fraction t(num);
    add(t);
    return *this;
}
fraction & fraction::operator-= (int num)
{
    fraction t(num);
    subtract(t);
    return *this;
}
fraction & fraction::operator*= (int num)
{
    fraction t(num);
    multiply(t);
    return *this;
}
fraction & fraction::operator/= (int num)
{
    fraction t(num);
    divide(t);
    return *this;
}

int fraction::compare(const fraction& t) const
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
bool fraction::operator== (const fraction& t) const
{
    return A * t.B == t.A * B;
    //return (A == t.A && B == t.B);
}

bool fraction::operator!= (const fraction& t) const
{
    return A * t.B != t.A * B;
}
bool fraction::operator> (const fraction& t) const
{
    return this->compare(t) == 1;
}
bool fraction::operator< (const fraction& t) const
{
    return this->compare(t) == -1;
}
bool fraction::operator>= (const fraction& t) const
{
    return this->compare(t) != -1;
}
bool fraction::operator<= (const fraction& t) const
{
    return this->compare(t) != 1;
}
bool fraction::operator== (double t) const
{
    return value() == t;
}

bool fraction::operator== (int t) const
{
    return A == t * B;
}
bool fraction::operator!= (int num) const
{
    return A != num * B;
}
bool fraction::operator> (int num) const
{
    return A > num * B;
}
bool fraction::operator< (int num) const
{
    return A < num * B;
}
bool fraction::operator>= (int num) const
{
    return A >= num * B;
}
bool fraction::operator<= (int num) const
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

fraction fraction::get_decimal_from_str(const std::string & str, size_t * idx)
{
    //只处理一个包含整数小数的字符串，返回一个fraction类
    static const std::string nums = "0123456789";
    std::string stra, strb; //新的字符串，存储小数a.b的a, b部分
    bool if_negative = false;

    std::size_t pos1 = str.find_first_of(nums);       //寻找第一个数字出现的位置
    if (pos1 == std::string::npos) return 0;          //没有找到任何可能的数字，返回0
    if (pos1 > 0) if_negative = (str[pos1-1] == '-'); //识别数字前边是否存在负号
    
    //寻找之后第一个不是数字的位置/潜在的小数点
    std::size_t pos2 = str.find_first_not_of(nums, pos1);  
    if (pos2 != std::string::npos) //若找到
    {
        if (pos2 == str.length() - 1) {
            if (idx != nullptr) *idx = pos2;
            stra = str.substr(pos1); //若索引位置出现在字符串末尾，则说明不会再有数据
        }
        else //位置出现在其他地方
        {
            if (str[pos2] != '.')      //索引位置终结于非小数点处，说明数据结束
            {
                if (idx != nullptr) *idx = pos2;
                stra = str.substr(pos1);
            }
            else if (str[pos2] == '.') //如果索引位置终结于小数点，说明之后可能还有数
            {
                //则继续查找非数字的位置
                std::size_t pos3 = str.find_first_not_of(nums, pos2+1); 
                if (pos3 == pos2 + 1) //非数字出现在小数点下一位
                {
                    if (idx != nullptr) *idx = pos2;
                    stra = str.substr(pos1);
                }
                else //非数字现于某个位置或未找到(返回值npos)
                {
                    //将小数a.b视作a,b两部分
                    //且能保证b部分存在，字符串非空
                    stra = str.substr(pos1,pos2-pos1);
                    if (pos3 == std::string::npos) {
                        strb = str.substr(pos2+1);
                    }
                    else {
                        if (idx != nullptr) *idx = pos3;
                        strb = str.substr(pos2+1,pos3-pos2-1);
                    }
                }
            }
        }
    }
    else stra = str.substr(pos1); //未找到，说明都是数字
    fraction t = 0;
    //字符串转int整型
    int a = 0, b = 0;
    try {a = std::stoi(stra);} catch (...) {a = 0;} //a部分的转换
    try {b = std::stoi(strb);} catch (...) {b = 0;} //b部分的转换
    if (if_negative) { a = -a; b = -b;}
    t += a; 
    t += fraction(b, pow(10, strb.length()));
    return t;
}

fraction fraction::construct_from_str(const std::string & str, size_t * idx)
{
    std::size_t sz = 0;
    fraction m = get_decimal_from_str(str,&sz); //处理分数线之前的部分
    std::size_t not_blank = str.find_first_not_of(" ",sz);
    
    if (not_blank == std::string::npos) //未找到分数线，说明可能仅有一个数
    {
        return m;
    }
    else if (str[not_blank] == '/' || str[not_blank] == '\\') //存在分数线
    {
        std::size_t sz1 = 0;
        fraction n = get_decimal_from_str(str.substr(not_blank),&sz1);   //处理分数线之后的部分
        if (idx) *idx = not_blank + sz1;
        if (n != 0) return m/n;
        else return m;
    }
    else {
        if (idx) *idx = sz;
        return m;
    }
}

fraction::fraction(const std::string & str)
{
    A = 0; B = 1; //init fraction as 0
    *this = construct_from_str(str);
}