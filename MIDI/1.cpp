#include <iostream>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <thread>
#include <functional>
#include <condition_variable>

#define BPM 100
#define DORIAN false

namespace gtup
{
    enum class VIRTUAL_KEY_CODE : int
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
        Z = 0x5A
    };

    std::unordered_map<std::string, VIRTUAL_KEY_CODE> sg_umapNoteToVKCode = {
        {"C1", VIRTUAL_KEY_CODE::Z},
        {"D1", VIRTUAL_KEY_CODE::X},
        {"E1", VIRTUAL_KEY_CODE::C},
        {"F1", VIRTUAL_KEY_CODE::V},
        {"G1", VIRTUAL_KEY_CODE::B},
        {"A1", VIRTUAL_KEY_CODE::N},
        {"B1", VIRTUAL_KEY_CODE::M},

        {"C2", VIRTUAL_KEY_CODE::A},
        {"D2", VIRTUAL_KEY_CODE::S},
        {"E2", VIRTUAL_KEY_CODE::D},
        {"F2", VIRTUAL_KEY_CODE::F},
        {"G2", VIRTUAL_KEY_CODE::G},
        {"A2", VIRTUAL_KEY_CODE::H},
        {"B2", VIRTUAL_KEY_CODE::J},

        {"C3", VIRTUAL_KEY_CODE::Q},
        {"D3", VIRTUAL_KEY_CODE::W},
        {"E3", VIRTUAL_KEY_CODE::E},
        {"F3", VIRTUAL_KEY_CODE::R},
        {"G3", VIRTUAL_KEY_CODE::T},
        {"A3", VIRTUAL_KEY_CODE::Y},
        {"B3", VIRTUAL_KEY_CODE::U}};

    std::unordered_map<std::string, std::string> sg_umapCMajorToDDorian = {
        {"C1", "B0"},
        {"C2", "B1"},
        {"C3", "B2"},

        {"D1", "C1"},
        {"D2", "C2"},
        {"D3", "C3"},

        {"E1", "D1"},
        {"E2", "D2"},
        {"E3", "D0"},

        {"F1", "E1"},
        {"F2", "E2"},
        {"F3", "E3"},

        {"G1", "F1"},
        {"G2", "F2"},
        {"G3", "F3"},

        {"A1", "G1"},
        {"A2", "G2"},
        {"A3", "G3"},

        {"B1", "A1"},
        {"B2", "A2"},
        {"B3", "A0"}};

    void KeyPress(gtup::VIRTUAL_KEY_CODE keyCode)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = (int)keyCode;
        input.ki.dwFlags = 0; // 0 表示按下按键

        SendInput(1, &input, sizeof(INPUT));
    }

    void KeyRelease(gtup::VIRTUAL_KEY_CODE keyCode)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = (int)keyCode;
        input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP 表示释放按键

        SendInput(1, &input, sizeof(INPUT));
    }
}

std::vector<std::vector<std::pair<std::string, int>>> tracks;
std::vector<std::thread> threads;
std::mutex mtx;
std::condition_variable cv;
auto clk = std::chrono::steady_clock::now();
std::atomic<int> ready(0);

void Input()
{
    std::string name = "flowerdance";

    std::fstream f;
    std::string song = "./song/";
    f.open(song + name + "/melody.txt");
    std::vector<std::pair<std::string, int>> notes;
    while (!f.eof())
    {
        std::string note;
        int time;
        f >> note >> time;
        notes.emplace_back(std::pair<std::string, int>(note, time));
    }
    tracks.emplace_back(notes);
    notes.clear();
    f.close();

    f.open(song + name + "/chord.txt");
    while (!f.eof())
    {
        std::string note;
        int time;
        f >> note >> time;
        notes.emplace_back(std::pair<std::string, int>(note, time));
    }
    tracks.emplace_back(notes);
    notes.clear();
    f.close();
}

std::function<void()> readyClearer = []()
{
    std::this_thread::sleep_for(std::chrono::microseconds(60000000 / BPM) / 2);
    ready = 0;
};

int main()
{
    Input();
    std::cout << "Input finished, press Enter to continue! " << std::endl;
    getchar();
    std::cout << "Program will start in 5 seconds! " << std::endl;

    std::function<void(std::vector<std::pair<std::string, int>>, int)> trackPlayer;
    trackPlayer = [](std::vector<std::pair<std::string, int>> track, int size)
    {
        std::this_thread::sleep_until(clk + std::chrono::microseconds(5000000));
        std::vector<std::string> mutiNotes;
        for (auto &[name, time] : track)
        {
            if (name == "LL")
            {
                std::unique_lock<std::mutex> lock(mtx);
                ready++;
                if (ready < size)
                {
                    cv.wait(lock, [&]()
                            { return ready >= size; });
                }
                else
                {
                    cv.notify_all();
                }
                std::thread t(readyClearer);
                t.detach();
                continue;
            }
            int last = 0;
            mutiNotes.emplace_back(name);
            if (time == 0)
            {
                continue;
            }
            else
            {
                last = 4 * 60000000 / (BPM * time);
                for (auto note : mutiNotes)
                {
                    std::string dn = note;
                    if (DORIAN)
                    {
                        dn = gtup::sg_umapCMajorToDDorian[note];
                    }
                    gtup::KeyPress(gtup::sg_umapNoteToVKCode[dn]);
                    gtup::KeyRelease(gtup::sg_umapNoteToVKCode[dn]);
                }
                std::this_thread::sleep_for(std::chrono::microseconds(last));
                mutiNotes.clear();
            }
        }
    };
    clk = std::chrono::steady_clock::now();
    for (const auto &track : tracks)
    {
        threads.emplace_back(trackPlayer, track, tracks.size());
    }
    for (auto &th : threads)
    {
        th.join();
    }
    system("pause");
}
