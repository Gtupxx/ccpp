#include <iostream>

template <typename... Args>
void print(Args... args)
{
    ((std::cout << args << ' '), ...);
    std::cout << '\n';
}

int main()
{
    print(1, 2, 3);          // 输出: 1 2 3
    print("hello", "world"); // 输出: hello world
    print(3.14, "pi");       // 输出: 3.14 pi
    return 0;
}
