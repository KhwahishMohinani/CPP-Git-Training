#include <iostream>

void C()
{
    throw -1;
    std::cout << "This is C block\n"; // This won't get printed
}

void B()
{
    C();
    /*catch(double x)
    {
        std::cout<<"This is catch block of B taking double as parameter\n";
    }*/
    // cannot have catch block without try block
}

void A()
{
    B();
}

int main()
{
    try
    {
        A();
    }
    catch (int x)
    {
        std::cout << "This is catch block in main taking int as parameter\n";
    }
    std::cout << "Program continues\n";
}