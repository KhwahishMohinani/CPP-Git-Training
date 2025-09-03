#include <iostream>

class Date
{
public:
    int day;
    int month;
    int year;

    void print(int a) // this should be void print() const
    {
        std::cout << day << "/" << month << "/" << year << "\n";
        a++; // can modify non member functions
    }
};

int main()
{
    const Date date{12, 9, 2025}; // const objects or variables must be intialized at the time of declaration
    const Date date2{};           // okay
    date.print(3);                // const object cannot call non const member functions
    // it guarantees it will not modify the object or call any non-const member functions
}