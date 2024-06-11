#include <iostream>
class CPerson
{
public:
    CPerson(std::string _name = "李华", int _age = 20, std::string _id = "000000000000000000")
        : name(_name), age(_age), id(_id){}

public:
    void setName(std::string _name)
    {
        this->name = _name;
    }
    void setAge(int _age)
    {
        this->age = _age;
    }
    void setId(std::string _id)
    {
        this->id = _id;
    }
    void show()
    {
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Age: " << this->age << std::endl;
        std::cout << "ID: " << this->id << std::endl;
    }

private:
    std::string name;
    int age;
    std::string id;
};

int main()
{
    CPerson non;
    non.show();
    CPerson WG("王刚", 19, "123123123123123123");
    WG.show();
    WG.setAge(30);
    WG.show();
    WG.setId("456456456456456456");
    WG.show();
    WG.setName("哈哈");
    WG.show();
}