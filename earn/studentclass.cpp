/*
 * @Author: 柚岩龙蜥 1152349903@qq.com
 * @Date: 2023-04-24 11:31:59
 * @LastEditors: 柚岩龙蜥 1152349903@qq.com
 * @LastEditTime: 2023-05-06 00:00:24
 * @FilePath: \Code\ccpp\earn\studentclass.cpp
 * @Description:  
 * 
 */
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class student
{
private:
    string id;
    string name;
    vector<int> score;
    int average = 0;

public:
    student(string _id = "000", string _name = "jack", vector<int> _score = {0, 0, 0})
        : id(_id), name(_name), score(_score)
    {
        average = accumulate(score.begin(), score.begin() + 2, 0) / 3;
    }
    void display()
    {
        cout << "id: " << id << "\tname: " << name << "\tscore: ";
        for_each(score.begin(), score.end(), [](int a)
                 { cout << a << '\t'; });
        cout << "average: " << average << endl;
    }
};

int main()
{
    vector<student> stu;

    vector<int> tscore;
    int sscore;
    string sid;
    string sname;
    int num;
    while(true)
    {
        int c;
        printf("1. Display all information\n");
        printf("2. Add a student\n");
        printf("3. Delete a student\n");
        printf("4. Exit\n");
        cin >> c;
        while(c>4||c<1)
            cin >> c;
        switch (c)
        {
        case 1:
            for (int i = 0; i < stu.size();i++)
            {
                cout << i + 1 << ':';
                stu[i].display();
            }
            break;
        case 2:
            tscore.clear();
            cout << "please input the id:\n";
            cin >> sid;
            cout << "please input the name: \n";
            cin >> sname;
            cout << "please input the scores :\n";
            cin >> sscore;
            tscore.push_back(sscore);
            cin >> sscore;
            tscore.push_back(sscore);
            cin >> sscore;
            tscore.push_back(sscore);
            stu.emplace_back(student(sid, sname, tscore));
            break;
        case 3:
            cout << "please input the number of the student:";
            cin >> num;
            num--;
            stu.erase(stu.begin() + num);

            break;
        case 4:
            return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}