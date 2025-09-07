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
    Parent *ptr, p; // parent class type pointer
    ptr = &p;
    ptr->print(); // Parent class print called

    Child c;
    ptr = &c;     // Pointer to parent class storing address of object class
    ptr->print(); // still parent class print called

    // to resolve this, use virtual function
}