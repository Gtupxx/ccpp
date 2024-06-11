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
#include <sstream>
#include <bits/stdc++.h>

#define BPM 100
#define DORIAN false

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
                    // TODO: Process the note
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

namespace gtup
{
    std::unordered_map<std::string, int> sg_umapTxt2Midi = {
        {"C0", 36},
        {"D0", 38},
        {"E0", 40},
        {"F0", 41},
        {"G0", 43},
        {"A0", 45},
        {"B0", 47},

        {"C1", 48},
        {"D1", 50},
        {"E1", 52},
        {"F1", 53},
        {"G1", 55},
        {"A1", 57},
        {"B1", 59},

        {"C2", 60},
        {"D2", 62},
        {"E2", 64},
        {"F2", 65},
        {"G2", 67},
        {"A2", 69},
        {"B2", 71},

        {"C3", 72},
        {"D3", 74},
        {"E3", 76},
        {"F3", 77},
        {"G3", 79},
        {"A3", 81},
        {"B3", 83}};

}

namespace gtup
{
    struct MidiMessage
    {
        std::string messageType;
        int note;
        int velocity;
        int time;
    };

    class CMidiTrack
    {
    public:
        void AppendMessage(gtup::MidiMessage msg)
        {
            m_vTrack.emplace_back(msg);
        }
    private:
        std::vector<gtup::MidiMessage> m_vTrack;
    };

    class CMidiFile : public CMidiTrack
    {
    public:
        void AppendTrack(gtup::CMidiTrack track);
        void SaveFile(std::string path);
        

    private:
        std::vector<gtup::CMidiTrack> m_vTracks;
        std::stringstream m_ssFile;
        int m_iBPM;
    };
}