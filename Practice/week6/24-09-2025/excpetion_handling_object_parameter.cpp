#include <iostream>

class Base
{
};

class Derived : public Base
{
};

int main()
{
    try
    {
        throw Derived{};
    }
    catch (Base &b)
    {
        std::cout << "This is catch block in main taking base class as parameter\n";
    }
    catch (Derived &d)
    {
        std::cout << "This is catch block in main taking derived class as parameter\n";
    }
    std::cout << "Program continues\n";
}

// The one exception to the no implicit cast rule is class inheritance.
// If you throw a derived class object, it can be caught by a handler that takes either the derived type or any of its base classes.