/*
 * @Author: 柚岩龙蜥
 * @Date: 2023-11-18 14:43:30
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2023-11-18 17:09:22
 * @FilePath: \ccpp\MIDI\monitor.cpp
 * @Description:
 *
 */
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <mutex>

std::mutex g_outputMutex; // 定义全局互斥锁

// MIDI回调函数

// MIDI回调函数
void CALLBACK midiCallback(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    if (wMsg == MIM_DATA)
    {
        // 处理接收到的MIDI消息
        auto message = static_cast<DWORD>(dwParam1);
        // 提取消息类型
        auto messageType = (message >> 4) & 0xF;
        // 提取 MIDI 通道号
        auto channel = message & 0xF;
        // 提取音符值
        auto note = (message >> 8) & 0x7F;

        // 提取 Pitch Wheel 信息
        if (messageType == 0xE)
        {
            // 提取 Pitch Wheel 值
            auto pitchValue = ((message >> 8) & 0x7F) | ((message >> 9) & 0x3F80);

            // 输出 Pitch Wheel 信息
            std::cout << "Received Pitch Wheel message - Value: " << pitchValue << ", Channel: " << channel << std::endl;
        }
        // 提取 Control Change 信息
        else if (messageType == 0xB)
        {
            // 提取 Control Change 编号
            auto controlNumber = (message >> 8) & 0x7F;
            // 提取 Control Change 值
            auto controlValue = (message >> 16) & 0x7F;

            // 输出 Control Change 信息
            std::cout << "Received Control Change message - Number: " << controlNumber << ", Value: " << controlValue << ", Channel: " << channel << std::endl;
        }

        // 对输出操作进行加锁
        std::lock_guard<std::mutex> lock(g_outputMutex);

        if (messageType == 0x9)
        {
            // Note On 消息
            std::cout << "Received Note On message - Note: " << note << ", Channel: " << channel << std::endl;
        }
        else if (messageType == 0x8)
        {
            // Note Off 消息
            std::cout << "Received Note Off message - Note: " << note << ", Channel: " << channel << std::endl;
        }
    }
}

int main()
{
    // 获取可用的 MIDI 输入设备数量
    UINT numDevices = midiInGetNumDevs();
    if (numDevices == 0)
    {
        std::cout << "No MIDI input devices available." << std::endl;
        return 0;
    }

    std::cout << "Available MIDI input devices:" << std::endl;

    // 遍历每个 MIDI 输入设备并打印设备标识符
    for (UINT deviceId = 0; deviceId < numDevices; deviceId++)
    {
        MIDIINCAPS deviceCaps;
        MMRESULT result = midiInGetDevCaps(deviceId, &deviceCaps, sizeof(deviceCaps));
        if (result == MMSYSERR_NOERROR)
        {
            std::wcout << "Device ID: " << deviceId << ", Name: " << deviceCaps.szPname << std::endl;
        }
    }
    std::cout << "Enter the Device ID: " << std::endl;
    int deviceID = 0;
    std::cin >> deviceID;

    // 打开MIDI输入设备
    HMIDIIN hMidiIn;
    if (midiInOpen(&hMidiIn, deviceID, reinterpret_cast<DWORD_PTR>(&midiCallback), 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
    {
        std::cout << "Failed to open MIDI input." << std::endl;
        return 0;
    }

    // 开始接收MIDI消息
    if (midiInStart(hMidiIn) != MMSYSERR_NOERROR)
    {
        std::cout << "Failed to start MIDI input." << std::endl;
        midiInClose(hMidiIn);
        return 0;
    }

    std::cout << "Listening for MIDI messages..." << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getchar();
    return 0;
}