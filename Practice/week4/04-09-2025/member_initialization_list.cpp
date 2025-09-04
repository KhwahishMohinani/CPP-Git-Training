#include <iostream>

class Date
{
    int m_day{3}; // ignored
    int m_month;
    int m_year;

public:
    Date(int day, int month, int year)
        : m_day{day}, m_month{month}, m_year{year} // order should be the same as declared
    {
        std::cout << "Constructor created: " << day << "/" << month << "/" << year << "\n";
    }
    void setvalue(int day, int month, int year)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }
    void print() const
    {
        std::cout << m_day << "/" << m_month << "/" << m_year << "\n";
    }
};

int main()
{
    Date date1{'a', true, 2};
    date1.print();
    Date date{12, 9, 2025};
    date.print();
    date.setvalue(8, 9, 2025);
    date.print();
}