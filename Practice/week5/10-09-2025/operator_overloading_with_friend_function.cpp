#include <iostream>

class Complex
{
    int a, b;

public:
    void setData(int x, int y)
    {
        a = x;
        b = y;
    }
    void showData()
    {
        std::cout << "a = " << a << "\n";
        std::cout << "b = " << b << "\n";
    }
    friend Complex operator-(Complex);
};

Complex operator-(Complex other)
{
    Complex temp;
    temp.a = -other.a;
    temp.b = -other.b;
    return temp;
}

int main()
{
    Complex c1;
    c1.setData(2, 3);
    Complex c2;
    c2 = -c1;
    c1.showData();
    c2.showData();
}