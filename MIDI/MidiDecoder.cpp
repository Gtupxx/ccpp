#include <iostream>
#include <fstream>
#include <thread>

unsigned int readVariableLengthValue(std::ifstream &file)
{
    unsigned int value = 0;
    unsigned char byte;
    do
    {
        file.read(reinterpret_cast<char *>(&byte), 1);
        value = (value << 7) | (byte & 0x7F);
    } while (byte & 0x80);
    return value;
}

int main()
{
    std::ifstream file("./midi/test.mid", std::ios::binary);
    if (!file)
    {
        std::cout << "Failed to open MIDI file." << std::endl;
        return 0;
    }

    // 读取头部标识
    char headerChunkID[4];
    file.read(headerChunkID, 4);

    // 读取头部大小
    unsigned int headerChunkSize;
    file.read(reinterpret_cast<char *>(&headerChunkSize), 4);

    // 读取格式类型
    unsigned short formatType;
    file.read(reinterpret_cast<char *>(&formatType), 2);

    // 读取轨道数
    unsigned short numTracks;
    file.read(reinterpret_cast<char *>(&numTracks), 2);

    // 读取分辨率
    unsigned short division;
    file.read(reinterpret_cast<char *>(&division), 2);

    std::cout << "Header Chunk ID: " << std::string(headerChunkID, 4) << std::endl;
    std::cout << "Header Chunk Size: " << headerChunkSize << std::endl;
    std::cout << "Format Type: " << formatType << std::endl;
    std::cout << "Number of Tracks: " << numTracks << std::endl;
    std::cout << "Division: " << division << std::endl;

    getchar();

    for (int track = 0; track < numTracks; track++)
    {
        // 读取轨道标识
        char trackChunkID[4]; 
        file.read(trackChunkID, 4);

        // 读取轨道大小
        unsigned int trackChunkSize;
        file.read(reinterpret_cast<char *>(&trackChunkSize), 4);

        // 解析轨道事件
        while (file.tellg() < (std::streampos)(trackChunkSize + 8))
        {
            // 读取 delta time
            unsigned int deltaTime = readVariableLengthValue(file);

            // 读取事件类型
            unsigned char eventType;
            file.read(reinterpret_cast<char *>(&eventType), 1);

            // 根据事件类型解析事件参数
            if (eventType == 0x80)
            {
                // Note Off 事件
                unsigned char noteNumber, velocity;
                file.read(reinterpret_cast<char *>(&noteNumber), 1);
                file.read(reinterpret_cast<char *>(&velocity), 1);

                std::cout << "Note Off Event: ";
                std::cout << "Note Number: " << static_cast<int>(noteNumber) << ", ";
                std::cout << "Velocity: " << static_cast<int>(velocity) << std::endl;
                // 处理 Note Off 事件
            }
            else if (eventType == 0x90)
            {
                // Note On 事件
                unsigned char noteNumber, velocity;
                file.read(reinterpret_cast<char *>(&noteNumber), 1);
                file.read(reinterpret_cast<char *>(&velocity), 1);

                std::cout << "Note On Event: ";
                std::cout << "Note Number: " << static_cast<int>(noteNumber) << ", ";
                std::cout << "Velocity: " << static_cast<int>(velocity) << std::endl;
                // 处理 Note On 事件
            }
            else if (eventType == 0xC0)
            {
                // Program Change 事件
                unsigned char programNumber;
                file.read(reinterpret_cast<char *>(&programNumber), 1);

                std::cout << "Program Change Event: ";
                std::cout << "Program Number: " << static_cast<int>(programNumber) << std::endl;
                // 处理 Program Change 事件
            }
            // 处理其他事件类型
        }
    }
}