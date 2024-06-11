#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// 一个辅助函数，用于将字符串转换为整数
int string_to_int(string s) {
    int result;
    stringstream ss(s);
    ss >> result;
    return result;
}

// 一个辅助函数，用于判断字符串是否以某个子串开头
bool starts_with(string s, string prefix) {
    return s.substr(0, prefix.size()) == prefix;
}

// 主函数
int main() {
    // 打开文件
    ifstream fin("data.txt");
    if (!fin) {
        cout << "无法打开文件" << endl;
        return -1;
    }
    
    // 定义一个三维向量，用于存储数据
    vector<vector<vector<int>>> data;
    
    // 定义一个临时变量，用于存储当前天数
    int day = 0;
    
    // 定义一个字符串变量，用于读取文件中的每一行
    string line;
    
    // 循环读取文件中的每一行，直到文件结束
    while (getline(fin, line)) {
        // 如果当前行是空行，跳过
        if (line.empty()) continue;
        
        // 如果当前行是以"第"开头的，说明是新的一天，增加天数，并在数据向量中添加一个新的二维向量
        if (starts_with(line, "第")) {
            day++;
            data.push_back(vector<vector<int>>());
        }
        
        // 如果当前行是以"生产线"开头的，说明是生产线的数据，提取出生产线编号和产品批次，并在数据向量中添加一个新的一维向量
        if (starts_with(line, "生产线")) {
            // 用空格分割字符串，得到四个子串
            vector<string> tokens;
            stringstream ss(line);
            string token;
            while (ss >> token) {
                tokens.push_back(token);
            }
            
            // 提取出生产线编号和产品批次，并转换为整数
            int line_num = string_to_int(tokens[1]);
            int product_num = tokens[2][0] - 'A'; // 将产品字母转换为数字，例如A对应0，B对应1，以此类推
            int batch_num = string_to_int(tokens[3]);
            
            // 在数据向量中添加一个新的一维向量，包含三个元素：生产线编号、产品编号和产品批次
            data[day-1].push_back(vector<int>{line_num, product_num, batch_num});
        }
    }
    
    // 关闭文件
    fin.close();
    
    // 输出数据向量的内容，用于测试
    for (int i = 0; i < data.size(); i++) {
        cout << "第" << i+1 << "天：" << endl;
        for (int j = 0; j < data[i].size(); j++) {
            cout << "生产线" << data[i][j][0] << " 产品" << char(data[i][j][1] + 'A') << ": " << data[i][j][2] << " 批次" << endl;
        }
        cout << endl;
    }
    
    return 0;
}
