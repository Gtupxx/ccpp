#include <iostream>
#include <vector>
#include <functional>
#include <time.h>

int __FAST_IO__ = []()
{
    std::ios::sync_with_stdio(1);
    std::cin.tie(0);
    std::cout.tie(0);
    return 0;
}();
class ysfcir
{
public:
    ysfcir(int _n = 30, int _m = 9) : n(_n), m(_m)
    {
        for (int i = 1; i <= n; i++)
        {
            list.emplace_back(i);
        }
    }
    void start()
    {
        std::cout << "sqlist\n";
        int cur = 0;
        typedef std::vector<int>::iterator vit;
        vit it = list.begin();
        while ((int)list.size() > n / 2)
        {
            int pos = (m + cur - 1) % list.size();
            std::cout << *(it + pos) << ' ';
            list.erase(it + pos);
            cur = pos;
        }
        std::cout << "has been killed\n";
    }
    void show()
    {
        std::function<void(int)> print;
        print = [](int n)
        {
            std::cout << ' ' << n;
        };
        std::cout << list[0];
        std::for_each(list.begin(), list.end(), print);
        std::cout << " is alive\n";
    }

private:
    int n;
    int m;
    std::vector<int> list;
};

struct linklist
{
    int data;
    linklist *next;
};
class ysfcir_2
{
public:
    ysfcir_2(int _n = 30, int _m = 9) : n(_n), m(_m)
    {
        list = new linklist;
        list->data = n;
        linklist *it = list;
        for (int i = 1; i <= n; i++)
        {
            it->next = new linklist;
            it = it->next;
            it->data = i;
        }
        it->next = nullptr;
    }
    void start()
    {
        std::cout << "linklist\n";
        int cur = 0;
        linklist *it = list->next;
        linklist *pre = list;
        while (list->data > n / 2)
        {
            int pos = (m + cur - 1) % list->data;
            if(pos>cur)
            {
                for (int i = 0; i < pos - cur; i++)
                {
                    pre = it;
                    it = it->next;
                }
            }
            else
            {
                it = list->next;
                pre = list;
                for (int i = 0; i < pos; i++)
                {
                    pre = it;
                    it = it->next;
                }
            }
            std::cout << it->data << ' ';
            pre->next = it->next;
            list->data--;
            delete it;
            it = pre->next;
            cur = pos;
        }
        std::cout << it->data << " has been killed \n";
    }
    void show()
    {
        linklist *it = list->next;
        while (it != nullptr)
        {
            std::cout << it->data << ' ';
            it = it->next;
        }
        std::cout << "is alive\n";
    }
private:
    int n;
    int m;
    linklist *list;
};

int main()
{
    time_t start,end;
    int n, m;
    std::cout << "Enter the number of travelers:";
    std::cin >> n;
    std::cout << "Enter the number :";
    std::cin >> m;
    //ysfcir是顺序表版本，ysfcir_2是链表版本
    start = clock();
    ysfcir a(n, m);
    // ysfcir_2 a(n, m);
    a.start();
    a.show();
    end = clock();
    std::cout << "time cost: " << end - start << " ms\n";
    system("pause");
    return 0;
}