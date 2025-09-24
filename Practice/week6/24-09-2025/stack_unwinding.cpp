#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "Constructor of class A\n";
    }
    ~A()
    {
        std::cout << "Destructor of class A\n";
    }
};

class B
{
public:
    B()
    {
        std::cout << "Constructor of class B\n";
    }
    ~B()
    {
        std::cout << "Destructor of class B\n";
    }
};

int main()
{
    try
    {
        std::cout << "In try block in main()\n";
        A a;
        B b;
        throw("Exception thrown in try block of main()\n"); // throw "msg"; → type is const char* and not string
        // Once throw is executed, local members get destroyed: firstly B then A. Its because Variable that is declared late maybe dependent of the previous variable
        // Objects are destroyed in reverse order of construction when stack unwinding happens during an exception.
    }
    catch (std::string e)
    {
        std::cout << "Exception: " << e << "\n";
    }
    catch (...) // This catch block will work
    {
        std::cout << "Some Exceptions caught in main()\n";
    }

    std::cout << "Resume Execution in main()\n";
}
