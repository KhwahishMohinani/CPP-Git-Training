#include <iostream>

class E
{
public:
    std::string message;
    E() : message("Class E\n") {};
};

void f()
{
    try
    {
        std::cout << "Try block of f()\n";
        E myException;
        throw myException;
    }
    catch (E &e)
    {
        std::cout << "Catch (E &e) block of f()\n";
        std::cout << "Exception: " << e.message;
        throw;
    }
}

int main()
{
    try
    {
        std::cout << "Try block of main()\n";
        f();
    }
    catch (...)
    {
        std::cout << "catch(...) block of main()\n";
    }
}