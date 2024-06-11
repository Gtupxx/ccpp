/*
 * @Author: 柚岩龙蜥
 * @Date: 2024-06-02 12:02:34
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-06-02 12:02:40
 * @FilePath: \ccpp\ex\FilesEqual.cpp
 * @Description:  
 * 
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

bool compareFiles(const std::string &file1, const std::string &file2)
{
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);

    if (!f1.is_open() || !f2.is_open())
    {
        std::cerr << "Unable to open files." << std::endl;
        return false;
    }

    // Read the files into vectors
    std::vector<char> buffer1(std::istreambuf_iterator<char>(f1), {});
    std::vector<char> buffer2(std::istreambuf_iterator<char>(f2), {});

    // Compare file sizes
    if (buffer1.size() != buffer2.size())
    {
        return false;
    }

    // Compare file contents
    return std::equal(buffer1.begin(), buffer1.end(), buffer2.begin());
}

int main()
{
    std::string file1 = "file1.txt";
    std::string file2 = "file2.txt";

    if (compareFiles(file1, file2))
    {
        std::cout << "Files are identical." << std::endl;
    }
    else
    {
        std::cout << "Files are different." << std::endl;
    }

    return 0;
}