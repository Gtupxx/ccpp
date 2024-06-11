#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <mutex>
#include <unordered_map>

enum class VirtualKeyCode : int
{
    A = 0x41,
    B = 0x42,
    C = 0x43,
    D = 0x44,
    E = 0x45,
    F = 0x46,
    G = 0x47,
    H = 0x48,
    I = 0x49,
    J = 0x4A,
    K = 0x4B,
    L = 0x4C,
    M = 0x4D,
    N = 0x4E,
    O = 0x4F,
    P = 0x50,
    Q = 0x51,
    R = 0x52,
    S = 0x53,
    T = 0x54,
    U = 0x55,
    V = 0x56,
    W = 0x57,
    X = 0x58,
    Y = 0x59,
    Z = 0x5A,

    n0 = 0x30,
    n1 = 0x31,
    n2 = 0x32,
    n3 = 0x33,
    n4 = 0x34,
    n5 = 0x35,
    n6 = 0x36,
    n7 = 0x37,
    n8 = 0x38,
    n9 = 0x39
};

std::unordered_map<unsigned long, VirtualKeyCode> keyMap = {
    {48, VirtualKeyCode::Z},
    {50, VirtualKeyCode::X},
    {52, VirtualKeyCode::C},
    {53, VirtualKeyCode::V},
    {55, VirtualKeyCode::B},
    {57, VirtualKeyCode::N},
    {59, VirtualKeyCode::M},

    {60, VirtualKeyCode::A},
    {62, VirtualKeyCode::S},
    {64, VirtualKeyCode::D},
    {65, VirtualKeyCode::F},
    {67, VirtualKeyCode::G},
    {69, VirtualKeyCode::H},
    {71, VirtualKeyCode::J},

    {72, VirtualKeyCode::Q},
    {74, VirtualKeyCode::W},
    {76, VirtualKeyCode::E},
    {77, VirtualKeyCode::R},
    {79, VirtualKeyCode::T},
    {81, VirtualKeyCode::Y},
    {83, VirtualKeyCode::U},
    {36, VirtualKeyCode::A},
    {37, VirtualKeyCode::S},
    {38, VirtualKeyCode::K},
    {39, VirtualKeyCode::L},

    {40, VirtualKeyCode::n1},
    {41, VirtualKeyCode::n2},
    {42, VirtualKeyCode::n3},
    {43, VirtualKeyCode::n4}};

std::mutex g_outputMutex; // 全局互斥锁

float g_axisX = 0.0f; // 摇杆XY
float g_axisY = 0.0f;

void KeyPress(VirtualKeyCode keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = (int)keyCode;
    input.ki.dwFlags = 0; // 0 表示按下按键

    SendInput(1, &input, sizeof(INPUT));
}

void KeyRelease(VirtualKeyCode keyCode)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = (int)keyCode;
    input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP 表示释放按键

    SendInput(1, &input, sizeof(INPUT));
}

void midiToKey(unsigned long note, bool press)
{
    if (press)
        KeyPress(keyMap[note]);
    else
        KeyRelease(keyMap[note]);
}

void joyToKey()
{
    if (g_axisX > 0.0f)
    {
        KeyRelease(VirtualKeyCode::A);
        KeyPress(VirtualKeyCode::D);
    }
    else if (g_axisX < 0.0f)
    {
        KeyRelease(VirtualKeyCode::D);
        KeyPress(VirtualKeyCode::A);
    }
    else
    {
        KeyRelease(VirtualKeyCode::A);
        KeyRelease(VirtualKeyCode::D);
    }

    if (g_axisY > 0.0f)
    {
        KeyRelease(VirtualKeyCode::S);
        KeyPress(VirtualKeyCode::W);
    }
    else if (g_axisY < 0.0f)
    {
        KeyRelease(VirtualKeyCode::W);
        KeyPress(VirtualKeyCode::S);
    }
    else
    {
        KeyRelease(VirtualKeyCode::W);
        KeyRelease(VirtualKeyCode::S);
    }
}

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

        std::lock_guard<std::mutex> lock(g_outputMutex);

        // 提取 Pitch Wheel 信息
        if (messageType == 0xE)
        {
            // 提取 Pitch Wheel 值
            auto pitchValue = ((message >> 8) & 0x7F) | ((message >> 9) & 0x3F80);

            std::cout << "Received Pitch Wheel message - Value: " << pitchValue << ", Channel: " << channel << std::endl;

            g_axisX = (pitchValue - 8192.0f) / 8192.0f;
            joyToKey();
        }
        // 提取 Control Change 信息
        else if (messageType == 0xB)
        {
            // 提取 Control Change 编号
            auto controlNumber = (message >> 8) & 0x7F;
            // 提取 Control Change 值
            auto controlValue = (message >> 16) & 0x7F;

            std::cout << "Received Control Change message - Number: " << controlNumber << ", Value: " << controlValue << ", Channel: " << channel << std::endl;

            g_axisY = (controlValue - 64.0f) / 64.0f;
            joyToKey();
        }
        // 提取 Note 信息
        else if (messageType == 0x9)
        {
            // Note On 消息
            std::cout << "Received Note On message - Note: " << note << ", Channel: " << channel << std::endl;
            midiToKey(note, true);
        }
        else if (messageType == 0x8)
        {
            // Note Off 消息
            std::cout << "Received Note Off message - Note: " << note << ", Channel: " << channel << std::endl;
            midiToKey(note, false);
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
