#include <iostream>

int main()
{
    int value = 5;
    const int *const ptr = &value;

    value = 8;
    std::cout << *ptr << '\n';

    return 0;
}