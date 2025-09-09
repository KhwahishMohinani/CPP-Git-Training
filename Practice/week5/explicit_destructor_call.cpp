#include <iostream>

class A
{
public:
    int a = 2;
    ~A()
    {
        std::cout << "Explicit Destructor called\n";
    }
};

int main()
{
    A a;
    std::cout << a.a << "\n";
    a.~A();
    std::cout << a.a << "\n";
}