#include <iostream>

class Parent
{
public:
    Parent(int x)
    {
        std::cout << "Parent class constructor called\n";
    }
};

class Base : public Parent
{
public:
    Base(int x, int y) : Parent(x)
    {
        std::cout << "Base class constructor called\n";
    }
};

int main()
{
    Base b(2, 3);
}