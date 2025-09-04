#include <iostream>

class Date
{
    int m_day;
    int m_month;
    int m_year;

public:
    Date(int day, int month, int year)
    {
        std::cout << "Constructor created: " << day << "/" << month << "/" << year << "\n";
    }
    void setvalue(int, int, int);
    void print() const
    {
        std::cout << m_day << "/" << m_month << "/" << m_year << "\n";
    }
};

void Date::setvalue(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

int main()
{
    Date date1{'a', true, 2};
    Date date{12, 9, 2025};
    date.print();
    date.setvalue(8, 9, 2025);
    date.print();
    Date date2 = Date{2, 1, 4}; // Constructor can also be invoked like this
}