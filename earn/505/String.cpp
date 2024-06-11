#include <iostream>
#include <cstring>

class String
{
public:
    String(int len)
    {
        m_data = new char[len + 1];
        m_len = len;
    }

    String(const char *str)
    {
        m_len = strlen(str);
        m_data = new char[m_len + 1];
        strcpy(m_data, str);
    }

    String(const String &other)
    {
        m_len = other.m_len;
        m_data = new char[m_len + 1];
        strcpy(m_data, other.m_data);
    }

    ~String()
    {
        delete[] m_data;
    }

    String &operator=(const String &other)
    {
        if (this != &other)
        {
            delete[] m_data;
            m_len = other.m_len;
            m_data = new char[m_len + 1];
            strcpy(m_data, other.m_data);
        }
        return *this;
    }

    String UnionChar(const String &other) const
    {
        int new_len = m_len + other.m_len;
        String result(new_len);
        strcpy(result.m_data, m_data);
        strcat(result.m_data, other.m_data);
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const String &str)
    {
        os << str.m_data;
        return os;
    }

private:
    char *m_data;
    int m_len;
};

int main()
{
    String s1(5);
    s1 = "world";
    String s2("hello");
    String s3(s1);
    String s4 = s2;
    String s5 = s2.UnionChar(s1);

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    std::cout << s4 << std::endl;
    std::cout << s5 << std::endl;

    return 0;
}

/**
 * 心得：
 * 使用了一个char的数组来保存字符串的信息
 * 构造函数使用了new来初始化空间，并在析构函数中使用delete释放了空间，避免了内存泄漏
 * 注意，这里申请的内存应为长度加一，最后的字符为'\0'。
 * 对于赋值构造函数，直接获取被复制对象的len并申请内存，之后使用strcpy函数进行内容的复制
 * 对于=运算符的重载，我们需要先释放掉原本的内存，并申请新的内存，之后进行复制即可
 * 对于UnionChar函数，我们只需使用strcat函数将新的内容加到原来的内容后，并且新构造一个对象
*/