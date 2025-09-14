#include <iostream>

class GrandParent
{
public:
    void print()
    {
        std::cout << "This is GrandParent class\n";
    }
};

class Parent1 : virtual public GrandParent
{
};

class Parent2 : virtual public GrandParent
{
};

class Child : public Parent1, public Parent2
{
};

int main()
{
    Child c;
    c.print();
}