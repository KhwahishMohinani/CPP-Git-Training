#include <iostream>
#include <typeinfo>

void nullify(int *&ptr2)
{
    ptr2 = nullptr;
}

int main()
{
    int x = 7;
    int *ptr = &x;
    if (ptr)
    {
        std::cout << "ptr is non-null\n";
    }
    else
    {
        std::cout << "ptr is null\n";
    }
    nullify(ptr);
    if (ptr)
    {
        std::cout << "ptr is non-null\n";
    }
    else
    {
        std::cout << "ptr is null\n";
    }
    return 0;
}