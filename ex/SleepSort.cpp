/*
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2023-01-01 15:20:09
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-07-05 16:09:16
 * @FilePath: \ccpp\ex\SleepSort.cpp
 * @Description:  
 * 
 */
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <sstream>
#include <string>
#include <mutex>
#include <algorithm>
#include <fstream>
#include <condition_variable>

#define MAX 1000
#define SIZE 1000

time_t st;

auto clk = std::chrono::steady_clock::now();

std::vector<std::thread *> thd;
std::vector<int> ans;
std::mutex mut;

void SleepSort(std::vector<int> &v, int accuracy = 10000)
{
    std::function<void(int, int,int)> SleepHelper;
    SleepHelper = [](int time, int acc,int size)
    {
        std::this_thread::sleep_until(clk + std::chrono::microseconds(size)+std::chrono::microseconds(time * acc));
        std::lock_guard<std::mutex> lock(mut);
        ans.emplace_back(time);
    };
    st = clock();
    clk = std::chrono::steady_clock::now();
    for (auto num : v)
    {
        std::thread *t = new std::thread(SleepHelper, num, accuracy, v.size());
        thd.push_back(t);
    }
    for (auto &th : thd)
    {
        th->join();
        delete th;
    }
    v.assign(ans.begin(), ans.end());
    ans.clear();
}
int main()
{
    std::ofstream datafile;
    datafile.open("./data.txt ", std::ios::out);
    std::vector<int> v;
    for (int i = 0; i < SIZE; i++)
    {
        v.push_back(rand() % MAX);
    }
    std::cout << "Sort started !" << std::endl;
    time_t start = clock();
    // std::sort(v.begin(), v.end());
    SleepSort(v);
    time_t end = clock();
    int pre = -1, cnt = 0;
    for (auto i : v)
    {
        if (i < pre)
            cnt++;
        datafile << i << std::endl;
        pre = i;
    }
    int mingap = 0;
    for (size_t i = 1; i < v.size(); i++)
    {
        bool flag = 1;
        for (size_t j = 0; j + i < v.size(); j++)
        {
            if (v[j] > v[j + i])
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            mingap = i;
            break;
        }
    }

    std::cout << std::endl
              << "mistakes: " << cnt << std::endl
              << "mingap: " << mingap << std::endl
              << "time: " << end - start << " ms" << std::endl;
    return 0;
}