#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <sstream>
#include <string>
#include <mutex>
#include <algorithm>
#include <fstream>
#include <condition_variable>

#define MAX 1000000
#define SIZE 1000000

int maxn = 1000;
int size = 1000;

int Partition(std::vector<int> &vec, int left, int right)
{
    int pivot = vec[left];
    while (left < right)
    {
        while (left < right && vec[right] >= pivot)
            right--;
        vec[left] = vec[right];
        while (left < right && vec[left] <= pivot)
            left++;
        vec[right] = vec[left];
    }
    vec[left] = pivot;
    return left;
}
void QuickSort(std::vector<int> &vec, int left, int right)
{
    if (left >= right)
        return;

    int pivot = Partition(vec, left, right);
    QuickSort(vec, left, pivot - 1);
    QuickSort(vec, pivot + 1, right);
}

void BubbleSort(std::vector<int> vec)
{
    int n = vec.size();

    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t j = 0; j < n - i - 1; ++j)
        {
            if (vec[j] > vec[j + 1])
            {
                int temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }
}

void RadixSort(std::vector<int> &vec)
{
    // 找到最大值
    int max = vec[0];
    for (size_t i = 1; i < vec.size(); i++)
    {
        if (vec[i] > max)
        {
            max = vec[i];
        }
    }

    // 从个位开始，对每一位进行排序
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        std::vector<int> output(vec.size());
        std::vector<int> count(10, 0);

        // 统计每个桶中的元素个数
        for (size_t i = 0; i < vec.size(); i++)
        {
            count[(vec[i] / exp) % 10]++;
        }

        // 将count数组中的元素改为前缀和
        for (size_t i = 1; i < count.size(); i++)
        {
            count[i] += count[i - 1];
        }

        // 将元素按照当前位的值放到对应的桶中
        for (size_t i = vec.size() - 1; i > 0; i--)
        {
            output[count[(vec[i] / exp) % 10] - 1] = vec[i];
            count[(vec[i] / exp) % 10]--;
        }

        // 将排序好的元素赋值回原向量
        for (size_t i = 0; i < vec.size(); i++)
        {
            vec[i] = output[i];
        }
    }
}

int main()
{
    std::ofstream datafile;
    datafile.open("./data.txt ", std::ios::out);

    for (maxn = 10000000; maxn <= 10000000; maxn += 5000)
    {
        for (size = 10000; size <= 1000000; size += 10000)
        {
            std::vector<int> v;
            srand(clock());
            v.clear();
            for (size_t i = 0; i < size; i++)
            {
                v.push_back(rand() % maxn);
            }

            // std::cout << "std::sort started !" << std::endl;
            time_t start = clock();
            // std::sort(v.begin(), v.end());
            time_t end = clock();
            // int t1 = end - start;
            // std::cout << "std::sort : time: " << t1 << " ms" << std::endl;
            // v.clear();
            // for (size_t i = 0; i < size; i++)
            // {
            //     v.push_back(rand() % maxn);
            // }

            // std::cout << "QuickSort started !" << std::endl;
            // start = clock();
            // QuickSort(v, 0, v.size() - 1);
            // end = clock();
            // int t2 = end - start;
            // std::cout << "QuickSort : time: " << t2 << " ms" << std::endl;
            // v.clear();
            // for (size_t i = 0; i < size; i++)
            // {
            //     v.push_back(rand() % maxn);
            // }

            start = clock();
            std::cout << "BubbleSort started !" << std::endl;
            BubbleSort(v);
            end = clock();
            int t3 = end - start;
            std::cout << "BubbleSort : time: " << t3 << " ms" << std::endl;
            v.clear();
            for (size_t i = 0; i < size; i++)
            {
                v.push_back(rand() % maxn);
            }

            // start = clock();
            // std::cout << "RadixSort started !" << std::endl;
            // RadixSort(v);
            // end = clock();
            // int t4 = end - start;
            // std::cout << "RadixSort : time: " << t4 << " ms" << std::endl;
            // v.clear();
            // for (size_t i = 0; i < size; i++)
            // {
            //     v.push_back(rand() % maxn);
            // }

            // datafile << "|  " << size << "\t|  " << maxn
            //          << "\t|  " << t1 << "\t|  " << t2 << "\t|  " << 0 << "\t|  " << t4 << "\t|  " << std::endl;
            
            datafile << "|  " << size << "\t|  " << maxn
                     << "\t|  " << t3 << "\t|  "<< std::endl;
        }
    }

    return 0;
}
