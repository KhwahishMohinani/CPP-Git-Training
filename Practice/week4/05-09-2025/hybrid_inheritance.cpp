#include <iostream>

class Parent1
{
public:
    void print()
    {
        std::cout << "This is parent 1 class\n";
    }
};

class Parent2
{
public:
    void print()
    {
        std::cout << "This is parent 2 class\n";
    }
};

class Child1 : public Parent1
{
public:
    void print()
    {
        std::cout << "This is Child1 class\n";
    }
};

class Child2 : public Parent1, public Parent2
{
public:
    void print()
    {
        std::cout << "This is Child2 class\n";
    }
};

int main()
{
    Child2 b;
    b.print();          // calls child class print
    b.Parent1::print(); // calls parent 1 class print
    b.Parent2::print(); // calls parent 2 class print
}