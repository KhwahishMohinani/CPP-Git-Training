#include <iostream>

class GrandParent
{
public:
    void print()
    {
        std::cout << "This is grand parent class\n";
    }
};

class Parent : public GrandParent
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
        std::cout << "This is Child class\n";
    }
};

int main()
{
    Child b;
    b.print();              // calls child class print
    b.Parent::print();      // calls parent class print
    b.GrandParent::print(); // calls grand parent class print
}