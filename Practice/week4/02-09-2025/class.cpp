#include <iostream>

void getHello();

class Date
{
    int day = 9;
    int month;
    int year;

public:
    void print()
    {
        std::cout << day << "/" << month << "/" << year << "\n";
    }

    void getHello()
    {
        std::cout << "Hello\n";
    }

    void getDate();
};

void Date::getDate()
{
    std::string s;
    std::cout << "Enter the date";
    std::cin >> s;
}

int main()
{
    Date today;
    // today.day = 02;
    today.print();
    today.getHello();
    today.getDate();
}