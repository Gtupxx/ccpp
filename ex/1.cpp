/*
 * @Author: 柚岩龙蜥
 * @Date: 2023-12-05 21:46:17
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-03-01 15:30:04
 * @FilePath: \ccpp\ex\1.cpp
 * @Description:  
 * 
 */
#include <bits/stdc++.h>
using namespace std;

struct A
{
    int a;
    int b;
    int c;
    A(int _a, int _b, int _c) : a(_a), b(_b), c(_c){};
    void print()
    {
        cout << a << ' ' << b << ' ' << c << endl;
    }
};

void mySort(vector<A> &vec)
{
    sort(vec.begin(), vec.end(), [](const A &f, const A &s)
         {
        if(f.a>s.a)
        {
            return true;
        }
        else if(f.a==s.a)
        {
            if(f.b>s.b)
            {
                return true;
            }
            else if(f.b==s.b)
            {
                if(f.c>s.c)
                {
                    return true;
                }
            }
        }
        return false; });
}

int main()
{
    vector<A> vec;
    vec.push_back(A{2, 2, 2});
    vec.push_back(A{1, 2, 3});
    vec.push_back(A{3, 2, 3});
    vec.push_back(A{2, 1, 3});
    vec.push_back(A{2, 2, 3});
    for(A a:vec)
    {
        a.print();
    }
    mySort(vec);
    cout << "After" << endl;
    for(A a:vec)
    {
        a.print();
    }
    return 0;
}