#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Rectangle
{
public:
    Rectangle(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_, double x4_, double y4_);
    bool check(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_, double x4_, double y4_);
    double getLength() const;
    double getWidth() const;
    double getPerimeter() const;
    double getArea() const;
    bool isSquare() const;

private:
    double m_x1, m_y1, m_x2, m_y2, m_x3, m_y3, m_x4, m_y4; // 保存长方形的4个顶点的坐标
    char m_fillchar = '*';
};

Rectangle::Rectangle(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_, double x4_, double y4_)
{
    if (check(x1_, y1_, x2_, y2_, x3_, y3_, x4_, y4_))
    {
        m_x1 = x1_;
        m_y1 = y1_;
        m_x2 = x2_;
        m_y2 = y2_;
        m_x3 = x3_;
        m_y3 = y3_;
        m_x4 = x4_;
        m_y4 = y4_;
    }
    else
    {
        cout << "Error: Invalid coordinates for rectangle!" << endl;
        exit(1);
    }
}

bool Rectangle::check(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_, double x4_, double y4_)
{
    if (x1_ > 0 && y1_ > 0 && x2_ > 0 && y2_ > 0 && x3_ > 0 && y3_ > 0 && x4_ > 0 && y4_ > 0)
    {
        double d1 = sqrt((x2_ - x1_) * (x2_ - x1_) + (y2_ - y1_) * (y2_ - y1_));
        double d2 = sqrt((x3_ - x2_) * (x3_ - x2_) + (y3_ - y2_) * (y3_ - y2_));
        double d3 = sqrt((x4_ - x3_) * (x4_ - x3_) + (y4_ - y3_) * (y4_ - y3_));
        double d4 = sqrt((x1_ - x4_) * (x1_ - x4_) + (y1_ - y4_) * (y1_ - y4_));

        double d5 = sqrt((x3_ - x1_) * (x3_ - x1_) + (y3_ - y1_) * (y3_ - y1_));
        double d6 = sqrt((x4_ - x2_) * (x4_ - x2_) + (y4_ - y2_) * (y4_ - y2_));

        double epsilon = 1e-5; // 设置一个误差范围
        if (abs(d1 - d3) < epsilon && abs(d2 - d4) < epsilon && abs(d5 - d6) < epsilon)
        {
            return true;
        }
    }
    return false;
}

double Rectangle::getLength() const
{
    double ab = sqrt((m_x2 - m_x1) * (m_x2 - m_x1) + (m_y2 - m_y1) * (m_y2 - m_y1));
    double ac = sqrt((m_x3 - m_x2) * (m_x3 - m_x2) + (m_y3 - m_y2) * (m_y3 - m_y2));
    return ab > ac ? ab : ac;
}

double Rectangle::getWidth() const
{
    double ab = sqrt((m_x2 - m_x1) * (m_x2 - m_x1) + (m_y2 - m_y1) * (m_y2 - m_y1));
    double ac = sqrt((m_x3 - m_x2) * (m_x3 - m_x2) + (m_y3 - m_y2) * (m_y3 - m_y2));
    return ab < ac ? ab : ac;
}

double Rectangle::getPerimeter() const
{
    double length = getLength();
    double width = getWidth();
    double perimeter = 2 * (length + width);
    return perimeter;
}

double Rectangle::getArea() const
{
    double length = getLength();
    double width = getWidth();
    double area = length * width;
    return area;
}

bool Rectangle::isSquare() const
{
    double length = getLength();
    double width = getWidth();

    double epsilon = 1e-5;
    return abs(length - width) < epsilon;
}

int main()
{
    Rectangle rect(1, 1, 10, 1, 10, 10, 1, 10);

    cout << "Perimeter: " << rect.getPerimeter() << endl;
    cout << "Area: " << rect.getArea() << endl;

    if (rect.isSquare())
    {
        cout << "This rectangle is a square." << endl;
    }
    else
    {
        cout << "This rectangle is not a square." << endl;
    }

    return 0;
}

/**
 * 心得：
 * 检查输入合理性：调用构造函数时应判断所构造的矩形是否合法，即对边应对应相等，对角线也应相等。
 * 浮点数的比较：由于计算机储存浮点数的原理，我们不能简单地使用“==”来判断两个浮点数是否相等，
 * 在本题中，我的做法是选取了一个较小的double 类型的值（1e-5），当误差的绝对值小于此范围时即判定为相等。
 * 输出长宽：应检查任意一组相临边，长为较长边的长度，宽为较短边的长度。
 * 
 */