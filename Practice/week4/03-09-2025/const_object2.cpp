#include <iostream>

class Date
{
public:
    int day;
    int month;
    int year;

    void print()
    {
        std::cout << day << "/" << month << "/" << year << "\n";
    }
};

void getHello(const Date &date)
{
    std::cout << "Hello";
    date.print(); // will not compile because date in this scope is const object trying to call non const member
}

int main()
{
    Date date{12, 9, 2025};
}