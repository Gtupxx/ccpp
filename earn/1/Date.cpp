#include <iostream>

class Date
{
public:
    Date(int y = 1970, int m = 1, int d = 1)
        : year(y), month(m), day(d)
        {
            if(m<0)
            {
                std::cout << "the month can not be negative !" << std::endl;
            }
            if(m>12)
            {
                std::cout << "the month can not be bigger than 12 !" << std::endl;
            }
            if(d<0)
            {
                std::cout << "the day can not be negative !" << std::endl;
            }
            if(d>31)
            {
                std::cout << "the day can not be bigger than 31 !" << std::endl;
            }
            if(y<0)
            {
                std::cout << "the year can not be negative !" << std::endl;
            }
        }

public:
    bool isSolarMonth()
    {
        bool flag = false;
        for(auto i : {1,3,5,7,8,10,11})
        {
            if(i==this->month)
            {
                flag = true;
            }
        }
        return flag;
    }
    bool isLeapYear()
    {
        bool flag = false;
        if((year%4==0&&year%100!=0)||year%400==0)
        {
            flag = true;
        }
        return flag;
    }
    void show()
    {
        std::cout << "Year:" << '\t' << year << std::endl;
        std::cout << "Month:" << '\t' << month << std::endl;
        std::cout << "Day:" << '\t' << day << std::endl;
    }
    void monthPlus1()
    {
        month++;
        if(month>12)
        {
            month -= 12;
            year++;
        }
    }
    void check()
    {
        if(isLeapYear())
        {
            std::cout << "is a leap year !" << std::endl;
        }
        else
        {
            std::cout << "is a common year !" << std::endl;
        }
        if(isSolarMonth())
        {
            std::cout << "is a solar month !" << std::endl;
        }
        else
        {
            std::cout << "is a lunar month !" << std::endl;
        }
    }

private:
    int year;
    int month;
    int day;
};

int main()
{
    Date today(2023, 3, 26);
    today.show();
    today.check();
    today.monthPlus1();
    today.show();
    today.check();
}