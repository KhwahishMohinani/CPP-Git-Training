#include <iostream>

class Parent
{
public:
    void print()
    {
        std::cout << "This is parent class\n";
    }
};

class Child : public Parent
{
public:
    void print()
    {
        std::cout << "This is Base class\n";
    }
};

int main()
{
    Child b;
    b.print();         // calls base class print
    b.Parent::print(); // calls parent class print
}