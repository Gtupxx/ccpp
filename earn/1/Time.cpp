#include<iostream>
/**
 * 解题思路：
 * 题目前面说只含时分，但是后面还是涉及到秒
 * 如果只含时分，后面的++运算符就没有意义了
 * 因此必须有秒
 * 私有成员有时分秒三个
 * 构造函数可以直接分别传入三个参数，默认为0
 * 对于+-运算符的重载
 * +运算符要考虑什么时候进位
 * -运算符考虑比较大小即可
 * 对于++运算符的重载，要注意返回值是左值还是右值
*/
 class Time
 {
private:
    int hours;
    int minutes;
    int seconds;
public:
    //构造函数可以实现（时）、（时，分）和（时，分，秒）初始化
    Time(int h=0,int m=0,int s=0)
    :hours(h),minutes(m),seconds(s)
    {
        minutes+=seconds/60;
        seconds%=60;
        hours+=minutes/60;
        minutes%=60;
        hours%=24;
    }
    Time operator +(Time a)//重载为成员函数
    {
        a.hours += this->hours;
        a.minutes += this->minutes;
        a.seconds += this->seconds;
        a.minutes += a.seconds / 60;
        a.seconds %= 60;
        a.hours += a.minutes / 60;
        a.seconds %= 60;
        a.hours %= 24;//超过24小时直接清零
        return a;
    }
    friend Time operator -(Time a,Time b)//重载为友元
    {
        /**
         * 题目要求返回时间差
         * 因此如果前面的时间小，应该反过来减
         * 可以直接取绝对值
         * 为方便计算，全部转换成秒为单位
        */
        int st=a.hours;
        st*=60;
        st+=a.minutes;
        st*=60;
        st+=a.seconds;
        int ed=b.hours;
        ed*=60;
        ed+=b.minutes;
        ed*=60;
        ed+=b.seconds;
        int result=abs(ed-st);
        Time ans(0,0,result);
        return ans;
    }
    Time & operator ++()//前缀
    {
        this->seconds++;
        this->minutes+=seconds/60;
        this->seconds%=60;
        this->hours+=minutes/60;
        this->minutes%=60;
        this->hours%=24;
        return *this;
    }
    Time operator ++(int)//后缀
    {
        Time temp(*this);
        this->seconds++;
        this->minutes+=seconds/60;
        this->seconds%=60;
        this->hours+=minutes/60;
        this->minutes%=60;
        this->hours%=24;
        return temp;
    }
    void display()//打印函数，方便调试
    {
        printf("%.2d %.2d %.2d\n",hours,minutes,seconds);
    }
 };

 int main()
 {
    Time a(22,0,0);
    Time b(21,02,35);
    Time c;
    c.display();
    b.display();
    (a+b).display();
    (a-b).display();

    //因为这个遍历太长了，就注释掉了
    //如果有需要可以去掉以下注释
    // for (int i = 0; i < 86400/2; i++)//遍历一天
    // {
    //     ++a;
    //     a.display();
    //     a++;
    //     a.display();
    // }
 }
 /**
  * 运行结果：（符合预期）
  * 
  * 00 00 00
  * 21 02 35
  * 19 02 35
  * 00 57 25
  * 
  * 由于遍历了一天，输出过长，不便展示
 */