#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <functional>

#define N 8

typedef std::vector<int>::iterator vit;

class CQueen
{
public:
    CQueen()
    {
        for (int i = 0; i < N; i++)
        {
            m.emplace_back(i);
        }
        for (int i = 0; i < N; i++)
        {
            std::vector<int> temp;
            for (int j = 0; j < i; j++)
            {
                temp.emplace_back(0);
            } 
            temp.emplace_back(1);
            while (temp.size() < N)
            {
                temp.emplace_back(0);
            }
            hh.emplace_back(temp);
        }
    }
    ~CQueen() {}
    std::vector<int> check()
    {
        std::sort(m.begin(), m.end());
        std::vector<int> res;
        for (auto i : m)
        {
            bool flag = true;
            for (int j = 1; j <= (int)m_stack.size(); j++)
            {
                if (m_stack[m_stack.size() - j] == i - j || m_stack[m_stack.size() - j] == i + j)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                res.emplace_back(i);
            }
        }
        return res;
    }
    void dfs()
    {
        if (m_stack.size() == N)
        {
            std::vector<std::vector<int>> temp;
            for (auto i : m_stack)
            {
                temp.emplace_back(hh[i]);
            }
            m_ans.emplace_back(temp);
            return;
        }
        std::vector<int> aviable_position = check();
        for (auto i : aviable_position)
        {
            vit it = std::find(m.begin(), m.end(), i);
            int cur = *it;
            m.erase(it);
            Push(cur);
            dfs();
            Pop();
            m.emplace_back(cur);
        }
    }
    void print()
    {
        std::ofstream file;
        file.open("./data.txt ", std::ios::out);
        for (int i = 0; i < (int)m_ans.size(); i++)
        {
            file << i + 1 << ": " << std::endl;
            std::function<void(std::vector<int>)> prt;
            prt = [&](std::vector<int> row)
            {
                std::for_each(row.begin(),
                              row.end(),
                              [&](int n)
                              {
                                  if (n == 0)
                                      file << "☆ ";
                                  else
                                      file << "★ ";
                              });
                file << std::endl;
            };
            std::for_each(m_ans[i].begin(),
                          m_ans[i].end(),
                          prt);
            file << '\n';
        }
    }
    int GetAnsSize()
    {
        return m_ans.size();
    }

private:
    int Pop()
    {
        vit it = m_stack.end();
        it--;
        int res = *it;
        m_stack.erase(it);
        return res;
    }
    void Push(int i)
    {
        m_stack.emplace_back(i);
    }

private:
    std::vector<int> m_stack;
    std::vector<int> m;
    std::vector<std::vector<int> > hh;
    std::vector<std::vector<std::vector<int> > > m_ans;
};

int main()
{
    CQueen a;
    a.dfs();
    a.print();
    std::cout << "We have find " << a.GetAnsSize() << " different answers.\n";
    std::cout << "The answers have been output into data.txt.\n";
    std::cout << "Press any key to continue . . .";
    return 0;
}