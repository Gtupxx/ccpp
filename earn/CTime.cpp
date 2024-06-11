/*
 * @Author: 柚岩龙蜥 1152349903@qq.com
 * @Date: 2023-04-24 10:22:59
 * @LastEditors: 柚岩龙蜥 1152349903@qq.com
 * @LastEditTime: 2023-05-05 23:53:44
 * @FilePath: \Code\ccpp\earn\CTime.cpp
 * @Description:  
 * 
 */
#include <iostream>
#include <time.h>
#include <windows.h>

class CTime
{
private:
    int hours;
    int minutes;
    int seconds;

public:
    CTime()
    {
        time_t now;
        time(&now); // 获取从1970至今过了多少秒，存入time_t类型的now
        time_t today = now % (24 * 60 * 60);    //now取86400的模，计算出距离当日0点的秒数
        hours = today /3600;
        hours += 8; //中国是东八区
        minutes = (today%3600)/60;
        seconds = today%60;
    }
    CTime operator++(int) // 后缀自增，实现加一秒
    {
        CTime temp(*this);
        this->seconds++;
        this->minutes += seconds / 60;
        this->seconds %= 60;
        this->hours += minutes / 60;
        this->minutes %= 60;
        this->hours %= 24;
        return temp;
    }
    void display() // 打印函数，方便调试
    {
        printf("%.2d %.2d %.2d\n", hours, minutes, seconds);
    }
};

int main()
{
    CTime a;
    while(true)
    {
        system("cls");
        a.display();
        a++;
        Sleep(1000);
    }
    return 0;
}