#include <iostream>

void func(int &&ref) // rvalue
{
    ref = 3;
}

void func(int &ref) // lvalue
{
    ref = 100;
}

int main()
{
    int x = 5;
    int &p = x;
    func(x);
    std::cout << "Value of x is: " << x << "\n";
    std::cout << "Value of p is: " << p << "\n";
    func(5);
}