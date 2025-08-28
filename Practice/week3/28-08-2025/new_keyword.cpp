#include <iostream>

int main()
{
    int *ptr = new int{42};
    std::cout << *ptr << "\n";
    delete ptr;

    ptr = new (std::nothrow) int; // when new couldn't allocate memory, it throws a bad allocation exception
    if (!ptr)
        std::cout << *ptr << "\n";
    delete ptr;
    return 0;
}