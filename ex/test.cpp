/*
 * @Author: 柚岩龙蜥
 * @Date: 2023-12-05 21:46:17
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-02-24 22:32:56
 * @FilePath: \ccpp\ex\test.cpp
 * @Description:
 *
 */
#include <Windows.h>
#include <thread>
#include <iostream>

void MouseClick(int x, int y)
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
    input.mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
    input.mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = 0;
    input.mi.time = 0;

    SendInput(1, &input, sizeof(INPUT));
}

int main()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    for (int i = 0; i < 5000; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        MouseClick(centerX, centerY);
    }

    return 0;
}