/*
 * @Author: 柚岩龙蜥 1152349903@qq.com
 * @Date: 2023-04-02 21:12:47
 * @LastEditors: 柚岩龙蜥 1152349903@qq.com
 * @LastEditTime: 2023-05-05 23:58:24
 * @FilePath: \Code\ccpp\earn\Student.cpp
 * @Description:  
 * 
 */
#include <iostream>

using namespace std;

class Student
{
public:
    Student(string _s_name = "Alice", float _contribute = 0.0f)
        : s_name(_s_name), contribute(_contribute) {}
    void Contribute(float con = 0.0f)
    {
        contribute += con;
        total += con;
        cout << s_name << "贡献了" << con << "块钱 !" << endl;
    }
    void Spend(float spd = 0.0f)
    {
        if (total >= spd)
        {
            total -= spd;
            contribute -= spd;
            cout << s_name << "花了" << spd << "块钱 !" << endl;
        }
        else
        {
            cout << s_name << "想花" << spd << "块钱"
                 << "但是班费不够 !" << endl;
        }
    }
    static void Display()
    {
        cout << "还剩" << total << "块钱 !" << endl;
    }

private:
    string s_name;
    float contribute;

private:
    static float total;
};
float Student::total = 0.0f;

int main()
{
    Student a("李华");
    Student b("小明");
    a.Contribute(100);
    b.Contribute(123);
    Student::Display();
    a.Spend(50);
    Student::Display();
    b.Spend(100);
    Student::Display();
    b.Spend(200);
}