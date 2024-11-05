/*
 * @Author: 柚岩龙蜥
 * @Date: 2024-04-06 14:36:37
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-04-06 14:41:25
 * @FilePath: \ccpp\ex\asdf.cpp
 * @Description:
 *
 */
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 50;
    int num = 0;
    ofstream file("data.txt", ios::out | ios::ate);
    cout.tie(0);
    ios::sync_with_stdio(false);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < 1000; ++k)
            {
                file << num++ << endl; // O(1000n^2)
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    std::cout <<"O(1000n^2) "<< "Elapsed time: " << duration << " ms\n";


    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // for (int k = 0; k < 1000; ++k)
            // {
                file << num++ << endl; // O(n^2)
            // }
        }
    }

    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    std::cout <<"O(n^2) "<< "Elapsed time: " << duration << " ms\n";

    return 0;
}