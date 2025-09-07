#include <iostream>

class Parent1
{
public:
    void print()
    {
        std::cout << "This is first parent class\n";
    }
};

class Parent2
{
public:
    void print()
    {
        std::cout << "This is second parent class\n";
    }
};

class Child : public Parent1, public Parent2
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
    b.print();          // calls child class print
    b.Parent1::print(); // calls parent1 class print
    b.Parent2::print(); // calls grand parent2 class print
}