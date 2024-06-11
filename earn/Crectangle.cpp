/*
 * @Author: 柚岩龙蜥 1152349903@qq.com
 * @Date: 2023-03-26 21:28:23
 * @LastEditors: 柚岩龙蜥 1152349903@qq.com
 * @LastEditTime: 2023-05-05 23:57:28
 * @FilePath: \Code\ccpp\earn\Crectangle.cpp
 * @Description:  
 * 
 */
#include <iostream>

class Crectangle
{
public:
    Crectangle(float lx=0.0f,float ly=0.0f,float rx=0.0f,float ry=0.0f)
    {
        //左上的x应是两个x坐标中最小的，y是两个y坐标中最大的，右下同理
        leup_x = lx < rx ? lx : rx;
        leup_y = ly > ry ? ly : ry;
        riwn_x = rx > lx ? rx : lx;
        riwn_y = ry < ly ? ry : ly;
    }
    void reSize(float lx=0.0f,float ly=0.0f,float rx=0.0f,float ry=0.0f)
    {
        //相当于重新构造一下
        leup_x = lx < rx ? lx : rx;
        leup_y = ly > ry ? ly : ry;
        riwn_x = rx > lx ? rx : lx;
        riwn_y = ry < ly ? ry : ly;
    }
    void move(float vx=0.0f,float vy=0.0f)//输入一个向量，按照向量来移动
    {
        leup_x += vx;
        riwn_x += vx;
        leup_y += vy;
        riwn_y += vy;
    }
    float Area()
    {
        int width = riwn_x - leup_x;
        int height = leup_y - riwn_y;
        return width * height;
    }
private:
//用左上和右下来确定矩形
    float leup_x;
    float leup_y;
    float riwn_x;
    float riwn_y;
};

int main()
{
    Crectangle tra(0,1,1,0);
    std::cout << tra.Area();
}