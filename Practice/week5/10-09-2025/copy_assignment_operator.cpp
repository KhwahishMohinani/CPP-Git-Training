#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "Default constructor";
    }
    A(int x)
    {
        std::cout << "Parameterised constructor\n";
        std::cout << x << "\n";
    }

    A(int x, int y)
    {
        std::cout << "Parameterised constructor\n";
        std::cout << x << "\t" << y << "\n";
    }

    A(A &x)
    {
        std::cout << "Copy constructor\n";
    }
};

int main()
{
    A a = 2;
    int x = 5, y = 6;
    A b = (x, y);
    /*(x, y) is the comma operator in C++:
    (x, y) → evaluates x (ignored), then y, and the whole expression yields the value of y.
    So (x, y) is just 6.*/
    A e = {x, y}; // This would work
    A d(x, y);
    A c = a;
}