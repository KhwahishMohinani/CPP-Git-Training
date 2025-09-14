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
    Parent *p;  // parent class type pointer
    p->print(); // Parent class print called

    Child c;
    p = &c;     // Pointer to parent class storing address of object class
    p->print(); // still parent class print called

    // to resolve this, use virtual function
}