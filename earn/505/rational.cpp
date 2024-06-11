#include <iostream>

using namespace std;

class Rational
{
public:
    Rational(int num = 0, int den = 1);
    void setNumerator(int num);
    void setDenominator(int den);
    void simplify();
    Rational operator-(const Rational &r) const;
    Rational operator*(const Rational &r) const;
    friend ostream &operator<<(ostream &os, const Rational &r);

private:
    int numerator;         // 分子
    int denominator;       // 分母
    int gcd(int a, int b); // 最大公约数
};

// 构造函数
Rational::Rational(int num, int den)
{
    if (den == 0)
    {
        cerr << "Error: Denominator cannot be zero." << endl;
        exit(1);
    }
    if (num == 0)
    {
        numerator = 0;
        denominator = 1;
    }
    else
    {
        int sign = ((num > 0 && den > 0) || (num < 0 && den < 0)) ? 1 : -1;
        num = abs(num);
        den = abs(den);
        int d = gcd(num, den);
        numerator = sign * num / d;
        denominator = den / d;
    }
}

void Rational::setNumerator(int num)
{
    numerator = num;
}

void Rational::setDenominator(int den)
{
    if (den == 0)
    {
        cerr << "Error: Denominator cannot be zero." << endl;
        exit(1);
    }
    denominator = den;
}

// 化简
void Rational::simplify()
{
    if (numerator == 0)
    {
        denominator = 1;
    }
    else
    {
        int sign = (numerator > 0) ? 1 : -1;
        int num = abs(numerator);
        int den = abs(denominator);
        int d = gcd(num, den);
        numerator = sign * num / d;
        denominator = den / d;
    }
}

// 求最大公约数
int Rational::gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

// 减法
Rational Rational::operator-(const Rational &r) const
{
    int num = numerator * r.denominator - r.numerator * denominator;
    int den = denominator * r.denominator;
    return Rational(num, den);
}

// 乘法
Rational Rational::operator*(const Rational &r) const
{
    int num = numerator * r.numerator;
    int den = denominator * r.denominator;
    return Rational(num, den);
}

// 重载输出运算符
ostream &operator<<(ostream &os, const Rational &r)
{
    os << r.numerator;
    if (r.denominator != 1)
    {
        os << "/" << r.denominator;
    }
    return os;
}

int main()
{
    Rational r1(3, 4);
    Rational r2(2, 3);
    Rational r3 = r1 - r2;
    Rational r4 = r1 * r2;

    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "r1 - r2 = " << r3 << endl;
    cout << "r1 * r2 = " << r4 << endl;

    return 0;
}
/**
 * 心得：
 * 分数的最简分数形式：在构造函数中，需要将输入的分子和分母化为最简分数形式。可以使用辗转相除法求最大公约数，然后分子除以最大公约数，分母除以最大公约数，得到最简分数形式。
 * 分母为0的情况：在构造函数和设置分母的函数中，需要判断分母是否为0。如果分母为0，则应该输出错误信息并退出程序。
 * 运算符的重载：减法需要对两个分数进行通分，乘法只需直接相乘，计算完成后需要进一步约分。
 * 输出运算符的重载：需要重载输出运算符，可以直接使用 cout 输出有理数对象。
*/