#ifndef _FRACTION_HPP_
#define _FRACTION_HPP_

#include <iostream>
#include <cmath>
#include <string>

template <typename IntType>
class fraction
{
private:
    IntType A; //numerator
    IntType B; //denominator
public:
    static IntType gcd(IntType x, IntType y) {
        do {
            x %= y;
            std::swap(x, y);
        } while (y);
        return x;
    }
    static IntType lcm(IntType a, IntType b) {
        if (a == 0 || b == 0) return 0;
        a /= gcd(a, b);
        return a * b;
    }

    static auto reduce(IntType a, IntType b) {
        using IntPair = std::pair<IntType, IntType>;
        bool negative = false;
        if (a == 0) { return IntPair(0, 1); }
        if ((a < 0 && b > 0) || (a > 0 && b < 0)) negative = true; // A*B < 0
        a = std::abs(a);
        b = std::abs(b);
        auto d = gcd(a, b);
        a /= d;
        b /= d;
        if (negative) a = -a;
        return IntPair(a, b);
    }

    void reduce() {
        bool negative = false;
        if (this->A == 0) { this->B = 1; return; }
        if ((this->A < 0 && this->B > 0) || (this->A > 0 && this->B < 0)) negative = true; // A*B < 0
        this->A = std::abs(this->A);
        this->B = std::abs(this->B);
        auto d = gcd(this->A, this->B);
        this->A /= d;
        this->B /= d;
        if (negative) this->A = -(this->A);
    }

    bool is_int() const {
        auto _A = std::abs(A);
        return _A == 0 || (_A >= B && _A % B == 0);
    }

    fraction & add(const fraction & other) {
        if (this->B == other.B) { this->A += other.A; }
        else if (other.B == 1) { this->A += (other.A * this->B); }
        else {
            auto lcm_of_denominators = lcm(B, other.B);
            auto multiplier_for_this  = lcm_of_denominators / B;
            auto multiplier_for_other = lcm_of_denominators / other.B;
            this->A *= multiplier_for_this;
            this->B *= multiplier_for_this;
            A += multiplier_for_other * other.A;
            this->reduce();
        }
        return *this;
    }

    fraction & add(IntType n) { A += n * B; return *this; }

    fraction & subtract(const fraction & other) {
        if (this->B == other.B) { this->A -= other.A; }
        else if (other.B == 1) { this->A -= (other.A * this->B); }
        else {
            auto lcm_of_denominators = lcm(B, other.B);
            auto multiplier_for_this  = lcm_of_denominators / B;
            auto multiplier_for_other = lcm_of_denominators / other.B;
            this->A *= multiplier_for_this;
            this->B *= multiplier_for_this;
            A -= multiplier_for_other * other.A;
            this->reduce();
        }
        return *this;
    }

    fraction & subtract(IntType n) { A -= n * B; return *this; }

    fraction & multiply(const fraction & other) {
        IntType divisor_1 = (this->A != 0) ? gcd(this->A, other.B) : 1;
        IntType divisor_2 = (other.A != 0) ? gcd(other.A, this->B) : 1;
        this->A /= divisor_1;
        this->B /= divisor_2;
        A *= (other.A / divisor_2);
        B *= (other.B / divisor_1);
        // if both are irreducible fractions, there's no need to reduce
        // this->reduce(); 

        // alternative:
        // auto pair_1 = reduce(this->A, addend.B);
        // auto pair_2 = reduce(addend.A, this->B);
        // this->A = pair_1.first  * pair_2.first;
        // this->B = pair_1.second * pair_2.second;

        // auto pair = reduce(this->A, this->B);
        // this->A = pair.first;
        // this->B = pair.second;
        return * this;
    }

    fraction & multiply(IntType val) {
        IntType gcd_ = gcd(this->B, val);
        this->B /= gcd_;
        val     /= gcd_;
        this->A *= val;
        return *this; 
    }

    fraction & divide(const fraction & other) {
        if (other == static_cast<IntType>(0)) { throw "cannot divided by 0!"; } // TODO
        IntType divisor_1 = gcd(this->B, other.B);
        IntType divisor_2 = (this->A != 0) ? gcd(this->A, other.A) : 1;
        A /= divisor_2;
        B /= divisor_1;
        A *= (other.B / divisor_1);
        B *= (other.A / divisor_2);
        // if both are irreducible fractions, there's no need to reduce
        // this->reduce();

        // alternative:
        // this->multiply( fraction(other.B, other.A) );

        return *this;
    }

    fraction & divide(IntType val) {
        IntType gcd_ = gcd(this->A, val);
        this->A /= gcd_;
        val     /= gcd_; 
        this->B *= val;
        return *this; 
    }

    double value() const { return static_cast<double>(A) / B; };

    fraction operator+(const fraction & other) const {
        return fraction(this->A, this->B).add(other);
    }

    fraction operator-(const fraction & other) const {
        return fraction(this->A, this->B).subtract(other);
    }

    fraction operator*(const fraction & other) const {
        return fraction(this->A, this->B).multiply(other);
    }

    fraction operator/(const fraction & other) const {
        return fraction(this->A, this->B).divide(other);
    }

    fraction operator+(IntType val) const {
        return fraction(this->A, this->B).add(val);
    }

    fraction operator-(IntType val) const {
        return fraction(this->A, this->B).subtract(val);
    }

    fraction operator*(IntType val) const {
        return fraction(this->A, this->B).multiply(val);
    }

    fraction operator/(IntType val) const {
        return fraction(this->A, this->B).divide(val);
    }

    fraction operator-() const { return fraction(-(this->A), this->B); }

    friend fraction operator+(IntType val, const fraction & frac) { return frac + val; }

    friend fraction operator-(IntType val, const fraction & frac) { return frac - val; }

    friend fraction operator*(IntType val, const fraction & frac) { return frac * val; }

    friend fraction operator/(IntType val, const fraction & frac) { return frac / val; }

    fraction & operator+=(const fraction & other) { return this->      add(other); }
    fraction & operator-=(const fraction & other) { return this-> subtract(other); }
    fraction & operator*=(const fraction & other) { return this-> multiply(other); }
    fraction & operator/=(const fraction & other) { return this->   divide(other); }

    fraction & operator+=(IntType val) { return this->      add(val); }
    fraction & operator-=(IntType val) { return this-> subtract(val); }
    fraction & operator*=(IntType val) { return this-> multiply(val); }
    fraction & operator/=(IntType val) { return this->   divide(val); }

    int compare(const fraction & other) const {
        if ((this->A < 0 && this->B > 0) || (this->A > 0 && this->B < 0)) {
            if (this->A < 0) return -1;
            if (other.A < 0) return  1;
        }
        if (this->A * other.B < other.A * this->B) return -1;
        else if (this->A * other.B == other.A * this->B) return 0;
        else return 1;
    }
    
    bool operator==(const fraction & other) const { return this->A * other.B == this->B * other.A; }
    bool operator!=(const fraction & other) const { return this->A * other.B != this->B * other.A; }
    bool operator> (const fraction & other) const { return this->compare(other) ==  1; }
    bool operator<=(const fraction & other) const { return this->compare(other) !=  1; }
    bool operator< (const fraction & other) const { return this->compare(other) == -1; }
    bool operator>=(const fraction & other) const { return this->compare(other) != -1; }

    bool operator==(IntType val) const { return A == val * this->B; }
    bool operator!=(IntType val) const { return A != val * this->B; }
    bool operator> (IntType val) const { return A >  val * this->B; }
    bool operator< (IntType val) const { return A <  val * this->B; }
    bool operator>=(IntType val) const { return A >= val * this->B; }
    bool operator<=(IntType val) const { return A <= val * this->B; }

    operator double() const { return this->value(); }

    friend std::string to_string(const fraction & f) {
        std::string str;
        if ( f < static_cast<IntType>(0) ) str += "-";
        if ( f.is_int() ) {
            str += std::to_string( std::abs(f.A) / f.B );
        } else {
            str += std::to_string( f.A );
            str += "/";
            str += std::to_string( f.B );
        }
        return str;
    }

    static fraction get_decimal_from_str(const std::string &, size_t *idx = nullptr);
    static fraction construct_from_str(const std::string &, size_t *idx = nullptr);

    fraction() : A(0), B(1) {}
    fraction(IntType val) : A(val), B(1) {}
    fraction(IntType a, IntType b) : A(a), B(b) { this->reduce(); }
    fraction(const std::string & str);
};

template <typename IntType>
fraction<IntType> fraction<IntType>::get_decimal_from_str(const std::string & str, size_t * idx)
{
    //只处理一个包含整数小数的字符串，返回一个fraction类
    static const std::string nums = "0123456789";
    std::string stra, strb; //新的字符串，存储小数a.b的a, b部分
    bool negative = false;

    std::size_t pos1 = str.find_first_of(nums);       //寻找第一个数字出现的位置
    if (pos1 == std::string::npos) return 0;          //没有找到任何可能的数字，返回0
    if (pos1 > 0) negative = (str[pos1-1] == '-'); //识别数字前边是否存在负号
    
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
    IntType a = 0, b = 0;
    try { a = std::stoi(stra); } catch (...) { a = 0; } //a部分的转换
    try { b = std::stoi(strb); } catch (...) { b = 0; } //b部分的转换
    if (negative) { a = -a; b = -b;}
    t += a; 
    t += fraction(b, static_cast<IntType>(std::pow(10, strb.length())));
    return t;
}

template <typename IntType>
fraction<IntType> fraction<IntType>::construct_from_str(const std::string & str, size_t * idx)
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
        if (n != static_cast<IntType>(0)) return m / n;
        else return m;
    }
    else {
        if (idx) *idx = sz;
        return m;
    }
}

template <typename IntType>
fraction<IntType>::fraction(const std::string & str) : fraction() // init fraction as 0
{
    *this = construct_from_str(str);
}

template <typename IntType>
std::istream & operator>>(std::istream & stream, fraction<IntType> & f) {
    std::string frac_as_str;
    stream >> frac_as_str;
    f = fraction<IntType>::construct_from_str(frac_as_str);
    return stream;
}

template <typename IntType>
std::ostream & operator<<(std::ostream & stream, const fraction<IntType> & f) 
{ 
    stream << to_string(f); 
    return stream; 
}

#endif
