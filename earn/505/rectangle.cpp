#include <iostream>

using namespace std;

class Rectangle
{
public:
    Rectangle(double l = 1.0, double w = 1.0);
    Rectangle(pair<double, double> p); // 转换构造函数
    double getLength() const;
    double getWidth() const;
    bool setLength(double l);
    bool setWidth(double w);
    double getPerimeter() const;
    double getArea() const;
    friend ostream &operator<<(ostream &os, const Rectangle &r); // 重载输出运算符
private:
    double length;
    double width;
};

Rectangle::Rectangle(double l, double w)
{
    if (setLength(l) == false || setWidth(w) == false)
    {
        cerr << "Error: Invalid length or width." << endl;
        exit(1);
    }
}
// 转换构造函数
Rectangle::Rectangle(pair<double, double> p)
{
    if (setLength(p.first) == false || setWidth(p.second) == false)
    {
        cerr << "Error: Invalid length or width." << endl;
        exit(1);
    }
}
double Rectangle::getLength() const
{
    return length;
}

double Rectangle::getWidth() const
{
    return width;
}

bool Rectangle::setLength(double l)
{
    if (l < 0.0 || l > 30.0)
    {
        return false;
    }
    length = l;
    return true;
}

bool Rectangle::setWidth(double w)
{
    if (w < 0.0 || w > 30.0)
    {
        return false;
    }
    width = w;
    return true;
}

double Rectangle::getPerimeter() const
{
    return 2 * (length + width);
}

double Rectangle::getArea() const
{
    return length * width;
}

ostream &operator<<(ostream &os, const Rectangle &r)
{
    os << "Length: " << r.length << ", Width: " << r.width;
    return os;
}

int main()
{
    Rectangle r1(5.0, 6.0);
    Rectangle r2(10.0, 10.0);
    Rectangle r3 = {15.0, 15.0};

    cout << "r1: " << r1 << endl;
    cout << "Perimeter of r1: " << r1.getPerimeter() << endl;
    cout << "Area of r1: " << r1.getArea() << endl;

    cout << "r2: " << r2 << endl;
    cout << "Perimeter of r2: " << r2.getPerimeter() << endl;
    cout << "Area of r2: " << r2.getArea() << endl;

    cout << "r3: " << r3 << endl;

    return 0;
}

/**
 * 数据类型：在类的设计中，需要选择合适的数据类型来存储和处理数据。
 * 成员函数：在编写成员函数时，需要考虑到可能出现的异常情况，并且进行相应的处理。例如，设置长度和宽度的函数中，判断输入的值是否在0.0到30.0之间，如果不在此范围内，则返回一个布尔值表示设置失败。
 * 友元函数：使用了友元函数来重载输出运算符。这使调试代码更加简单，但是也可能破坏类的封装性。
 * 转换构造函数：使用了pair<double,double>作为参数，这样可以直接用例如：Rectangle r1 = {12, 12}; 的方法进行构造。
 */