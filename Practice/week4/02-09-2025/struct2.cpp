#include <iostream>

struct Date
{
    int date{};
    int month{};
    int year{};
};

void printDate(Date date)
{
    std::cout << date.date << "/" << date.month << "/" << date.year << "\n";
}

int main()
{
    Date date{2, 7, 25};
    printDate(date);
    return 0;
}