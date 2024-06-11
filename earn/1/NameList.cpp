#include<iostream>
#include<set>
/**
 * 解题思路：
 * 私有成员显然只有name和age；
 * 为方便排序，选用全局变量agelist来保存所有人的年龄
 * 题目要求minage时刻为当前所有对象的最小年龄，需要经常排序
 * 因此选用multiset来自动实现
 * 每当调用构造函数时存入age，并更新minage
 * 为防止构造时不填参数，默认为李华，20岁
 * 析构函数会将当前对象的年龄删除，并更新minage
 */
std::multiset<int> agelist;
class People
{
private:
    std::string name;
    short age;
public:
    static short minage;
    People(std::string name_="李华",short age_=20)//默认为李华，20岁
    :name(name_),age(age_)
    {
        agelist.emplace(age_);//将新年龄插入到agelist中
        minage = *agelist.begin();//容器会自动升序排序
    }
    ~People()
    {
        agelist.erase(agelist.find(this->age));//删掉对象的年龄
        minage = *agelist.begin();//更新minage
    }
    void display() { std::cout << name << ' ' << age << std::endl; }//打印，方便调试
};
short People::minage = 0;
int main()
{
    People *a = new People("张三", 27);
    People *b = new People("李四", 25);
    a->display();
    b->display();
    std::cout <<"minage:"<< People::minage << std::endl;
    People *c=new People;
    c->display();
    std::cout <<"minage:"<< People::minage << std::endl;
    std::cout << "delete 李华" << std::endl;
    delete c;
    std::cout <<"minage:"<< People::minage << std::endl;
    std::cout << "delete 李四" << std::endl;
    delete b;
    std::cout <<"minage:"<< People::minage << std::endl;
}
/**
 * 运行结果：（符合预期）
 * 
 * 张三 27
 * 李四 25
 * minage:25
 * 李华 20
 * minage:20
 * delete 李华
 * minage:25
 * delete 李四
 * minage:27
*/