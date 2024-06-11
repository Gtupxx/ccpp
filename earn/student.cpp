/*
 * @Author: 柚岩龙蜥 1152349903@qq.com
 * @Date: 2023-04-24 10:51:28
 * @LastEditors: 柚岩龙蜥 1152349903@qq.com
 * @LastEditTime: 2023-05-05 23:59:58
 * @FilePath: \Code\ccpp\earn\student1.cpp
 * @Description:  
 * 
 */
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<string> id;
    vector<string> name;
    vector<vector<int>> score;

    string sid, sname;
    vector<int> tscore;
    int sscore;
    int num;
    while (true)
    {
        int c;
        printf("1. Display all information\n");
        printf("2. Add a student\n");
        printf("3. Delete a student\n");
        printf("4. Exit\n");
        cin >> c;
        switch (c)
        {
        case 1:
            for (int i = 0; i < (int)id.size(); i++)
            {
                int tot = 0;
                cout << i + 1 << ": "
                     << "id :" << id[i] << '\t' << "name: " << name[i] << '\t';
                for (int j = 0; j < 3; j++)
                {
                    tot += score[i][j];
                    cout << "score" << j + 1 << ": " << score[i][j] << '\t';
                }
                cout << "total score : " << tot << "\taverage score:" << tot / 3 << endl;
            }
            break;
        case 2:
            tscore.clear();
            cout << "please input the id:\n";
            cin >> sid;
            id.push_back(sid);
            cout << "please input the name: \n";
            cin >> sname;
            name.push_back(sname);
            cout << "please input the scores :\n";
            cin >> sscore;
            tscore.push_back(sscore);
            cin >> sscore;
            tscore.push_back(sscore);
            cin >> sscore;
            tscore.push_back(sscore);
            score.push_back(tscore);
            break;
        case 3:
            cout << "please input the number of the student:";
            cin >> num;
            num--;
            id.erase(id.begin() + num);
            name.erase(name.begin() + num);
            score.erase(score.begin() + num);

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