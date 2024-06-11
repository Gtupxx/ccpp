/*
 * @Author: 柚岩龙蜥
 * @Date: 2024-04-08 22:49:39
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-06-04 22:58:57
 * @FilePath: \ccpp\ex\digui.cpp
 * @Description:
 *
 */
#include <bits/stdc++.h>
using namespace std;

struct packed_struct
{
    unsigned int f1 : 1;
    unsigned int f2 : 1;
    unsigned int f3 : 1;
    unsigned int f4 : 1;
    unsigned int type : 4;
    unsigned int my_int : 9;
};

int main()
{
    packed_struct t;
    t.f1 = 0b1;
    t.f2 = 0b0;
    t.f3 = 0b1;
    t.f4 = 0b0;
    t.type = 0b1011;
    t.my_int = 0b000011111;
    auto *p = &t;
    int *pt = reinterpret_cast<int*>(p);
    cout << *pt; // result: 8117
}