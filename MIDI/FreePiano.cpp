/*
 * @Author: 柚岩龙蜥
 * @Date: 2023-12-05 21:46:17
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-01-09 12:50:20
 * @FilePath: \ccpp\MIDI\FreePiano.cpp
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

    enum class SCAN_KEY_CODE : int
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

    static std::unordered_map<std::string, VIRTUAL_KEY_CODE> sg_umapNoteToVKCode = {
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

    static std::unordered_map<std::string, SCAN_KEY_CODE> sg_umapNoteToSKCode = {

        {"C0", SCAN_KEY_CODE::Z},
        {"D0", SCAN_KEY_CODE::X},
        {"E0", SCAN_KEY_CODE::C},
        {"F0", SCAN_KEY_CODE::V},
        {"G0", SCAN_KEY_CODE::B},
        {"A0", SCAN_KEY_CODE::N},
        {"B0", SCAN_KEY_CODE::M},

        {"C1", SCAN_KEY_CODE::A},
        {"D1", SCAN_KEY_CODE::S},
        {"E1", SCAN_KEY_CODE::D},
        {"F1", SCAN_KEY_CODE::F},
        {"G1", SCAN_KEY_CODE::G},
        {"A1", SCAN_KEY_CODE::H},
        {"B1", SCAN_KEY_CODE::J},

        {"C2", SCAN_KEY_CODE::Q},
        {"D2", SCAN_KEY_CODE::W},
        {"E2", SCAN_KEY_CODE::E},
        {"F2", SCAN_KEY_CODE::R},
        {"G2", SCAN_KEY_CODE::T},
        {"A2", SCAN_KEY_CODE::Y},
        {"B2", SCAN_KEY_CODE::U},

        {"C3", SCAN_KEY_CODE::Num1},
        {"D3", SCAN_KEY_CODE::Num2},
        {"E3", SCAN_KEY_CODE::Num3},
        {"F3", SCAN_KEY_CODE::Num4},
        {"G3", SCAN_KEY_CODE::Num5},
        {"A3", SCAN_KEY_CODE::Num6},
        {"B3", SCAN_KEY_CODE::Num7},

        {"C4", SCAN_KEY_CODE::Num8},
        {"D4", SCAN_KEY_CODE::Num9},
        {"E4", SCAN_KEY_CODE::Num0},
        {"F4", SCAN_KEY_CODE::Minus},
        {"G4", SCAN_KEY_CODE::Equal},
        {"A4", SCAN_KEY_CODE::Backspace}

    };

    static std::unordered_map<std::string, std::string> sg_umapCMajorToDDorian = {
        {"C1", "D0"},
        {"C2", "D1"},
        {"C3", "D2"},
        {"C4", "D3"},

        {"D1", "E1"},
        {"D2", "E2"},
        {"D3", "E3"},
        {"D4", "E4"},

        {"E1", "F1"},
        {"E2", "F2"},
        {"E3", "F3"},
        {"E4", "F4"},

        {"F1", "G1"},
        {"F2", "G2"},
        {"F3", "G3"},
        {"F4", "G4"},

        {"G1", "A1"},
        {"G2", "A2"},
        {"G3", "A3"},
        {"G4", "A4"},

        {"A1", "B1"},
        {"A2", "B2"},
        {"A3", "B3"},
        {"A4", "B4"},

        {"B1", "C2"},
        {"B2", "C3"},
        {"B3", "C4"},
        {"B4", "C5"}};
}

namespace gtup
{
    /**
     * @description: Simulates keyboard key presses
     * @param {VirtualKeyCode} keyCode
     * @return {*}
     */
    void KeyDown(gtup::SCAN_KEY_CODE keyCode)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = (int)keyCode;
        input.ki.wScan = (int)keyCode;
        input.ki.dwFlags = KEYEVENTF_SCANCODE; // 表示扫描码

        SendInput(1, &input, sizeof(INPUT));
    }

    /**
     * @description: Simulates keyboard key releases
     * @param {VirtualKeyCode} keyCode
     * @return {*}
     */
    void KeyUp(gtup::SCAN_KEY_CODE keyCode)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = (int)keyCode;
        input.ki.wScan = (int)keyCode;
        input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; // 表示释放按键

        SendInput(1, &input, sizeof(INPUT));
    }

    class CText2Midi
    {
    public:
        CText2Midi(std::vector<std::string> _paths = {}, int _bpm = 100) : m_vPaths(_paths), m_iBPM(_bpm)
        {
            m_aiReady = 0;
            m_clk = std::chrono::steady_clock::now();

            for (auto p : m_vPaths)
            {
                m_vTracks.emplace_back(gtup::CText2Midi::__Input(p));
            }
            std::cout << "Input finished! " << std::endl;

            std::cout << "Merging tracks..." << std::endl;
            m_vMergedTrack = __MergeTracks(m_vTracks);
            std::cout << "Merging finished! " << std::endl;

            if (m_iBPM <= 0)
            {
                m_iBPM = 60;
            }
        }

        /**
         * @description:Play music with different mode
         * @param {bool} singleFlag     use the single-thread mode
         * @param {bool} dorianFlag     use the Dorian mode
         * @param {int} _bpm     set the BPM
         * @return {*}
         */
        void Play(bool singleFlag = false, bool dorianFlag = false, int _bpm = -1)
        {
            SetBPM(_bpm);

            std::cout << "The program will start in 5 seconds! " << std::endl;

            if (!singleFlag)
            {
                // muti-thread
                for (const auto &track : m_vTracks)
                {
                    m_vThreadPool.emplace_back(m_fnTrackPlayer, track, m_vTracks.size(), dorianFlag);
                }
            }
            else if (singleFlag)
            {
                // single thread
                m_vThreadPool.emplace_back(m_fnTrackPlayer, m_vMergedTrack, 0, dorianFlag);
            }

            for (auto &th : m_vThreadPool)
            {
                th.join();
            }
            m_vThreadPool.clear();

            std::cout << "Over..." << std::endl;
        }

        /**
         * @description: set the BPM
         * @param {int} _bpm ( > 0)
         * @return {*}
         */
        void SetBPM(int _bpm)
        {
            if (_bpm > 0)
            {
                m_iBPM = _bpm;
            }
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
         * @description: Merge every single tracks in the param
         * @param {vector<std::vector<std::pair<std::string, int>>>} mutiTrack
         * @return {std::vector<std::pair<std::string, int>>} singleTrack
         */
        std::vector<std::pair<std::string, int>> __MergeTracks(std::vector<std::vector<std::pair<std::string, int>>> tracks)
        {
            std::vector<std::pair<std::string, int>> res;
            // std::vector<int> gcb;
            int tick = 1;
            int tickCount = 0;
            std::vector<int> pass(tracks.size(), 0);
            std::vector<std::size_t> index(tracks.size(), 0);
            for (auto track : tracks)
            {
                for (auto [note, time] : track)
                {
                    if (note == "LL")
                    {
                        tickCount = tickCount > time ? tickCount : time;
                        continue;
                    }
                    if (time == 0)
                    {
                        continue;
                    }
                    tick = tick * time / __gcd(tick, time);
                }
            }

            for (int i = 0; i < tick * tickCount; i++)
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
                        pass[t] += tick / tracks[t][index[t]].second;
                        index[t]++;
                    }
                }
                notes.emplace_back(std::pair<std ::string, int>("H0", tick));

                for (int j = 0; j < (int)notes.size() - 1; j++)
                {
                    res.emplace_back(std::pair<std::string, int>(notes[j].first, 0));
                }
                res.emplace_back(std::pair<std::string, int>(notes.back().first, tick));
            }
            __MergeNotes(res);
            return res;
        }

        /**
         * @description: this does what you think it does
         */
        int __gcd(int x, int y)
        {
            while (y ^= x ^= y ^= x %= y)
                ;
            return x;
        }

    private:
        std::mutex m_mtx;
        std::condition_variable m_cv;
        std::chrono::_V2::steady_clock::time_point m_clk;

        std::vector<std::vector<std::pair<std::string, int>>> m_vTracks;
        std::vector<std::thread> m_vThreadPool;
        std::atomic<int> m_aiReady;
        std::vector<std::string> m_vPaths;
        std::vector<std::pair<std::string, int>> m_vMergedTrack;

        int m_iBPM;
        int m_iPressTime = 200;

    private:
        std::function<void()> m_fnClearReady = [this]()
        {
            std::this_thread::sleep_for(std::chrono::microseconds(60000000 / m_iBPM) / 2);
            m_aiReady = 0;
        };

        std::function<void(gtup::SCAN_KEY_CODE)> m_fnShortPress = [this](gtup::SCAN_KEY_CODE keyCode)
        {
            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = (int)keyCode; 
            input.ki.wScan = (int)keyCode;
            input.ki.dwFlags = KEYEVENTF_SCANCODE; // 表示扫描码

            SendInput(1, &input, sizeof(INPUT));
            input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP 表示释放按键

            std::this_thread::sleep_for(std::chrono::milliseconds(m_iPressTime));
            SendInput(1, &input, sizeof(INPUT));
        };

        std::function<void(std::vector<std::pair<std::string, int>>, int, bool)> m_fnTrackPlayer = [this](std::vector<std::pair<std::string, int>> singleTrack, int trkcnt, bool dorianFlag = false)
        {
            m_clk = std::chrono::steady_clock::now();
            std::this_thread::sleep_until(m_clk + std::chrono::microseconds(5000000));
            m_clk = std::chrono::steady_clock::now();

            std::vector<std::string> mutiNotes;
            for (auto &[name, time] : singleTrack)
            {
                if (name == "LL")
                {
                    std::unique_lock<std::mutex> lock(m_mtx);
                    m_aiReady++;
                    if (m_aiReady < trkcnt)
                    {
                        m_cv.wait(lock, [&]()
                                  { return m_aiReady >= trkcnt; });
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
                    last = 4 * 60000000 / (m_iBPM * time);
                    for (auto note : mutiNotes)
                    {
                        std::string dn = note;
                        if (dorianFlag)
                        {
                            dn = gtup::sg_umapCMajorToDDorian[note];
                        }
                        std::thread press(m_fnShortPress, gtup::sg_umapNoteToSKCode[dn]);
                        press.detach();
                    }
                    std::this_thread::sleep_until(m_clk + std::chrono::microseconds(last));
                    mutiNotes.clear();
                }
                m_clk = std::chrono::steady_clock::now();
            }
        };
    };

}

int main()
{
    std::vector<std::string> paths;
    paths.emplace_back("./song/flowerdance/melody.txt");
    paths.emplace_back("./song/flowerdance/chord.txt");

    gtup::CText2Midi p(paths, 100);
    p.Play(false, false);
}