#include <iostream>

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
};

int main()
{
    Date today;
    // today.day = 02;
    today.print();
}