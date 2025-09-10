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
    friend std::istream &operator>>(std::istream &din, Complex &c1);
    friend std::ostream &operator<<(std::ostream &dout, Complex &c1);
};

std::istream &operator>>(std::istream &din, Complex &c1)
{
    din >> c1.a >> c1.b;
    return din;
}

std::ostream &operator<<(std::ostream &dout, Complex &c1)
{
    dout << "a = " << c1.a << "\nb = " << c1.b << "\n";
    return dout;
}

int main()
{
    Complex c1;
    std::cout << "Enter a complex number: ";
    std::cin >> c1;
    std::cout << c1;
}