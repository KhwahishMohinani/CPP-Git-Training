#include <iostream>

class Parent
{
public:
    void print()
    {
        std::cout << "This is parent class\n";
    }
};

class Child1 : public Parent
{
public:
    void print()
    {
        std::cout << "This is Child1 class\n";
    }
};

class Child2 : public Parent
{
public:
    void print()
    {
        std::cout << "This is Child2 class\n";
    }
};

int main()
{
    Child1 b;
    b.print();         // calls child class print
    b.Parent::print(); // calls parent class print
}