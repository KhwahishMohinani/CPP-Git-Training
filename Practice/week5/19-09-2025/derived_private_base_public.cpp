#include <iostream>

class Base
{
public:
    virtual void print()
    {
        std::cout << "Base class print\n";
    }
};

class Derived : public Base
{
private:
    void print()
    {
        std::cout << "Derived class print\n";
    }
};

int main()
{
    Derived d;
    Base &b = d; //  derived class object in base class reference

    b.print();
    // d.print();  // inaccessible
}

// we can access derived class private member function(only overrider) through base class pointer or reference if in base class it is written in public and virtual