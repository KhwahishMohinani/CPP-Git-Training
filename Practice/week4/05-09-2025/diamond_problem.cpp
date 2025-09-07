#include <iostream>

class GrandParent
{
public:
    void print()
    {
        std::cout << "This is GrandParent class\n";
    }
};

class Parent1 : public GrandParent
{
};

class Parent2 : public GrandParent
{
};

class Child : public Parent1, public Parent2
{
};

int main()
{
    Child c;
    c.print(); // print function from GrandParent class
    // Abiguity arises, as Child now has two copies of print()
    // The ambiguity arises because the derived class has multiple paths to access members or methods inherited from the common ancestor, leading to confusion during method resolution and member access.

    // This can be resolved using virtual inheritance
}