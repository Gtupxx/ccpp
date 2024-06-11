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

    void setFillChar(const char &ch);
    void draw() const;
    void scale(double factor);
    void move(double dx, double dy);

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

// 下面是第四题添加的代码

void Rectangle::setFillChar(const char &ch)
{
    m_fillchar = ch;
}

void Rectangle::draw() const
{
    // 找到最小和最大的 x 和 y 坐标
    double minX = min(min(m_x1, m_x2), min(m_x3, m_x4));
    double minY = min(min(m_y1, m_y2), min(m_y3, m_y4));
    double maxX = max(max(m_x1, m_x2), max(m_x3, m_x4));
    double maxY = max(max(m_y1, m_y2), max(m_y3, m_y4));

    // 计算矩形的宽度和高度
    int width = static_cast<int>(ceil(maxX - minX));
    int height = static_cast<int>(ceil(maxY - minY));

    // 绘制矩形
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double x = j + minX;
            double y = i + minY;
            // 判断当前像素点是否在矩形内部
            if (x >= m_x1 && x <= m_x3 && y >= m_y1 && y <= m_y3)
            {
                cout << m_fillchar;
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void Rectangle::scale(double factor)
{
    // 计算矩形的中心点坐标
    double centerX = (m_x1 + m_x2 + m_x3 + m_x4) / 4;
    double centerY = (m_y1 + m_y2 + m_y3 + m_y4) / 4;

    // 对每个顶点进行缩放
    m_x1 = centerX + factor * (m_x1 - centerX);
    m_y1 = centerY + factor * (m_y1 - centerY);
    m_x2 = centerX + factor * (m_x2 - centerX);
    m_y2 = centerY + factor * (m_y2 - centerY);
    m_x3 = centerX + factor * (m_x3 - centerX);
    m_y3 = centerY + factor * (m_y3 - centerY);
    m_x4 = centerX + factor * (m_x4 - centerX);
    m_y4 = centerY + factor * (m_y4 - centerY);
}

void Rectangle::move(double dx, double dy)
{
    // 对每个顶点进行平移
    m_x1 += dx;
    m_y1 += dy;
    m_x2 += dx;
    m_y2 += dy;
    m_x3 += dx;
    m_y3 += dy;
    m_x4 += dx;
    m_y4 += dy;
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
    rect.draw();
    rect.setFillChar('&');
    rect.scale(2);
    rect.draw();

    return 0;
}

/**
 * 心得：
 * 绘制矩形：可以通过遍历矩形附近的坐标，并判断是否位于该矩形内部。
 * 矩形的缩放：矩形缩放前后的中心点是没有改变的，因此可以通过中心点来实现缩放。
 */