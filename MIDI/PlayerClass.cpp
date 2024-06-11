/*
 * @Author: 柚岩龙蜥
 * @Date: 2023-12-05 21:46:17
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2023-12-14 12:09:07
 * @FilePath: \ccpp\MIDI\PlayerClass.cpp
 * @Description:
 *
 */
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
#include <algorithm>

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

    enum class ScanCode : int
    {
        Tilde = 0x29,
        Num1 = 0x02,
        Num2 = 0x03,
        Num3 = 0x04,
        Num4 = 0x05,
        Num5 = 0x06,
        Num6 = 0x07,
        Num7 = 0x08,
        Num8 = 0x09,
        Num9 = 0x0a,
        Num0 = 0x0b,
        Minus = 0x0c,
        Equal = 0x0d,
        Backspace = 0x0e,
        Tab = 0x0f,
        Q = 0x10,
        W = 0x11,
        E = 0x12,
        R = 0x13,
        T = 0x14,
        Y = 0x15,
        U = 0x16,
        I = 0x17,
        O = 0x18,
        P = 0x19,
        LeftBracket = 0x1a,
        RightBracket = 0x1b,
        Enter = 0x1c,
        LeftCtrl = 0x1d,
        A = 0x1e,
        S = 0x1f,
        D = 0x20,
        F = 0x21,
        G = 0x22,
        H = 0x23,
        J = 0x24,
        K = 0x25,
        L = 0x26,
        Semicolon = 0x27,
        SingleQuote = 0x28,
        Backtick = 0x29,
        LeftShift = 0x2a,
        Backslash = 0x2b,
        Z = 0x2c,
        X = 0x2d,
        C = 0x2e,
        V = 0x2f,
        B = 0x30,
        N = 0x31,
        M = 0x32,
        Comma = 0x33,
        Period = 0x34,
        Slash = 0x35,
        RightShift = 0x36,
        NumpadStar = 0x37,
        LeftAlt = 0x38,
        Space = 0x39,
        CapsLock = 0x3a,
        F1 = 0x3b,
        F2 = 0x3c,
        F3 = 0x3d,
        F4 = 0x3e,
        F5 = 0x3f,
        F6 = 0x40,
        F7 = 0x41,
        F8 = 0x42,
        F9 = 0x43,
        F10 = 0x44,
        NumLock = 0x45,
        ScrollLock = 0x46,
        Numpad7 = 0x47,
        Numpad8 = 0x48,
        Numpad9 = 0x49,
        NumpadMinus = 0x4a,
        Numpad4 = 0x4b,
        Numpad5 = 0x4c,
        Numpad6 = 0x4d,
        NumpadPlus = 0x4e,
        Numpad1 = 0x4f,
        Numpad2 = 0x50,
        Numpad3 = 0x51,
        Numpad0 = 0x52,
        NumpadPeriod = 0x53,
        F11 = 0x57,
        F12 = 0x58,
        NumpadEnter = 0x9c,
        RightCtrl = 0xe01d,
        NumpadSlash = 0xe035,
        PrintScreen = 0xe037,
        RightAlt = 0xe038,
        Home = 0xe047,
        UpArrow = 0xe048,
        PageUp = 0xe049,
        LeftArrow = 0xe04b,
        RightArrow = 0xe04d,
        End = 0xe04f,
        DownArrow = 0xe050,
        PageDown = 0xe051,
        Insert = 0xe052,
        Delete = 0xe053,
        LeftWin = 0xe05b,
        RightWin = 0xe05c,
        Menu = 0xe05d
    };
    
    std::unordered_map<std::string, VIRTUAL_KEY_CODE> noteMapVK = {
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

        
    std::unordered_map<std::string, ScanCode> noteMapSC = {
        {"C1", ScanCode::Z},
        {"D1", ScanCode::X},
        {"E1", ScanCode::C},
        {"F1", ScanCode::V},
        {"G1", ScanCode::B},
        {"A1", ScanCode::N},
        {"B1", ScanCode::M},

        {"C2", ScanCode::A},
        {"D2", ScanCode::S},
        {"E2", ScanCode::D},
        {"F2", ScanCode::F},
        {"G2", ScanCode::G},
        {"A2", ScanCode::H},
        {"B2", ScanCode::J},

        {"C3", ScanCode::Q},
        {"D3", ScanCode::W},
        {"E3", ScanCode::E},
        {"F3", ScanCode::R},
        {"G3", ScanCode::T},
        {"A3", ScanCode::Y},
        {"B3", ScanCode::U}};

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
}

namespace gtup
{
    /**
     * @description: Simulates keyboard key presses
     * @param {VirtualKeyCode} keyCode
     * @return {*}
     */
    void KeyPress(gtup::ScanCode keyCode)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = (int)keyCode;
        input.ki.wScan = (int)keyCode;
        input.ki.dwFlags = KEYEVENTF_SCANCODE; // 0 表示按下按键

        SendInput(1, &input, sizeof(INPUT));
    }

    /**
     * @description: Simulates keyboard key releases
     * @param {VirtualKeyCode} keyCode
     * @return {*}
     */
    void KeyRelease(gtup::ScanCode keyCode)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = (int)keyCode;
        input.ki.wScan = (int)keyCode;
        input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP 表示释放按键

        SendInput(1, &input, sizeof(INPUT));
    }

    void ShortPress(gtup::ScanCode keyCode)
    {
        KeyPress(keyCode);
        Sleep( (rand() % 15 + 5) );
        KeyRelease(keyCode);
    }


    class CAutoPlayer
    {
    public:
        CAutoPlayer(std::vector<std::string> _paths = {}) : m_vPaths(_paths)
        {
            m_aiReady = 0;
            m_clk = std::chrono::steady_clock::now();
        }

        void Run()
        {
            std::vector<std::vector<std::pair<std::string, int>>> tracks;
            for (auto s : m_vPaths)
            {
                tracks.emplace_back(gtup::CAutoPlayer::__Input(s));
            }
            std::cout << "Input finished, press 's' for single-thread, 'm' for muti-thread! " << std::endl;
            char c = getchar();

            std::function<void(std::vector<std::pair<std::string, int>>, int)> trackPlayer;
            trackPlayer = [this](std::vector<std::pair<std::string, int>> track, int size)
            {
                m_clk = std::chrono::steady_clock::now();
                std::this_thread::sleep_until(m_clk + std::chrono::microseconds(5000000));
                m_clk = std::chrono::steady_clock::now();

                std::vector<std::string> mutiNotes;
                for (auto &[name, time] : track)
                {
                    if (name == "LL")
                    {
                        std::unique_lock<std::mutex> lock(m_mtx);
                        m_aiReady++;
                        if (m_aiReady < size)
                        {
                            m_cv.wait(lock, [&]()
                                    { return m_aiReady >= size; });
                        }
                        else
                        {
                            m_cv.notify_all();
                        }
                        std::thread t(m_fnClearReady);
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
                            ShortPress(gtup::noteMapSC[dn]);
                        }
                        std::this_thread::sleep_until(m_clk + std::chrono::microseconds(last));
                        mutiNotes.clear();
                    }
                    m_clk = std::chrono::steady_clock::now();
                }
            };

            if (c == 'm')
            {
                // muti-thread
                std::cout << "The program will start in 5 seconds! " << std::endl;
                for (const auto &track : tracks)
                {
                    thrdPool.emplace_back(trackPlayer, track, tracks.size());
                }
                for (auto &th : thrdPool)
                {
                    th.join();
                }
            }
            else if (c == 's')
            {
                // single thread
                std::cout << "Merging tracks..." << std::endl;
                std::vector<std::pair<std::string, int>> mergedTrack = __MergeTracks(tracks);
                std::cout << "Merging finished, the program will start in 5 seconds! " << std::endl;
                std::thread player(trackPlayer, mergedTrack, 0);
                player.join();
            }

            system("pause");
        }

    private:
        /**
         * @description: Input music from path
         * @param {string} path
         * @return {*}
         */
        std::vector<std::pair<std::string, int>> __Input(std::string path)
        {
            std::vector<std::pair<std::string, int>> res;
            std::fstream f;

            f.open(path);
            while (!f.eof())
            {
                std::string note;
                int time;
                f >> note >> time;
                res.emplace_back(std::pair<std::string, int>(note, time));
            }
            return res;
        }

        std::function<void()> m_fnClearReady = [this]()
        {
            std::this_thread::sleep_for(std::chrono::microseconds(60000000 / BPM) / 2);
            m_aiReady = 0;
        };

        int __gcd(int x, int y)
        {
            while (y ^= x ^= y ^= x %= y)
                ;
            return x;
        }

        /**
         * @description: Merge the useless notes
         * @param {vector<std::pair<std::string, int>>} &notes
         * @return {*}
         */
        void __MergeNotes(std::vector<std::pair<std::string, int>> &notes)
        {
            std::pair<std::string, int> pre = notes.front();
            bool flag = true;
            while (flag)
            {
                flag = false;
                for (std::size_t i = 1; i < notes.size(); i++)
                {
                    if (notes[i].second == 0 || pre.second == 0)
                    {
                        pre = notes[i];
                        continue;
                    }
                    if (notes[i].first == "H0")
                    {
                        if (notes[i].second != pre.second)
                        {
                            // different time
                            int big = std::max(notes[i].second, pre.second);
                            int sml = std::min(notes[i].second, pre.second);
                            if (big % sml != 0)
                            {
                                pre = notes[i];
                                continue;
                            }
                            else if (big % (1 + big / sml) != 0)
                            {
                                pre = notes[i];
                                continue;
                            }
                            else
                            {
                                flag = true;
                                notes[i - 1].second = big / (1 + big / sml);
                                notes.erase(notes.begin() + i);
                            }
                        }
                        else
                        {
                            // same time
                            if (pre.first == "H0")
                            {
                                if (notes[i].first == "H0")
                                {
                                    flag = true;
                                    notes.erase(notes.begin() + i);
                                    notes[i - 1].second /= 2;
                                }
                                else
                                {
                                    continue;
                                }
                            }
                        }
                    }
                    pre = notes[i];
                }
            }
        }

        /**
         * @description: Merge all the tracks in the param
         * @param {vector<std::vector<std::pair<std::string, int>>>} tracks
         * @return {std::vector<std::pair<std::string, int>>} singleTrack
         */
        std::vector<std::pair<std::string, int>> __MergeTracks(std::vector<std::vector<std::pair<std::string, int>>> tracks)
        {
            std::vector<std::pair<std::string, int>> res;
            std::vector<int> gcb;
            int dt = 1;
            int nl = 0;
            std::vector<int> pass(tracks.size(), 0);
            std::vector<std::size_t> index(tracks.size(), 0);
            for (auto track : tracks)
            {
                for (auto [note, time] : track)
                {
                    if (note == "LL")
                    {
                        nl = nl > time ? nl : time;
                        continue;
                    }
                    if (time == 0)
                    {
                        continue;
                    }
                    dt = dt * time / __gcd(dt, time);
                }
            }

            for (int i = 0; i < dt * nl; i++)
            {
                std::vector<std::pair<std::string, int>> notes;
                for (std::size_t t = 0; t < tracks.size(); t++)
                {
                    if (index[t] >= tracks[t].size())
                    {
                        continue;
                    }
                    if (pass[t] == i)
                    {
                        if (tracks[t][index[t]].first == "LL")
                        {
                            index[t]++;
                        }
                        while (tracks[t][index[t]].second == 0)
                        {
                            notes.emplace_back(std::pair<std ::string, int>(tracks[t][index[t]]));
                            index[t]++;
                        }
                        notes.emplace_back(tracks[t][index[t]]);
                        pass[t] += dt / tracks[t][index[t]].second;
                        index[t]++;
                    }
                }
                notes.emplace_back(std::pair<std ::string, int>("H0", dt));

                for (int j = 0; j < (int)notes.size() - 1; j++)
                {
                    res.emplace_back(std::pair<std::string, int>(notes[j].first, 0));
                }
                res.emplace_back(std::pair<std::string, int>(notes.back().first, dt));
            }
            __MergeNotes(res);
            return res;
        }

    private:
        std::vector<std::thread> thrdPool;
        std::mutex m_mtx;
        std::condition_variable m_cv;
        std::chrono::_V2::steady_clock::time_point m_clk = std::chrono::steady_clock::now();
        std::atomic<int> m_aiReady;
        std::vector<std::string> m_vPaths;
    };

}

int main()
{
    std::vector<std::string> paths;
    paths.emplace_back("./song/flowerdance/melody.txt");
    paths.emplace_back("./song/flowerdance/chord.txt");

    gtup::CAutoPlayer p(paths);
    p.Run();
}




