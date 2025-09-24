#include <iostream>

void C()
{
    throw -1;
}

void A()
{
    C();
}

int main()
{
    try
    {
        A();
    }
    catch (double x) // No implicit conversion in catch block
    {
        std::cout << "This is catch block in main taking double as parameter\n";
    }
    catch (int x)
    {
        std::cout << "This is catch block in main taking int as parameter\n";
    }
    std::cout << "Program continues\n";
}