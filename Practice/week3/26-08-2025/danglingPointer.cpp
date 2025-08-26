#include <iostream>

int main()
{
    int x = 8;
    int *ptr = &x;
    std::cout << "The value stored at address pointer is pointing to is: " << *ptr << "\n";
    {
        int y = 2;
        ptr = &y;
        std::cout << "The value stored at address pointer is pointing to is: " << *ptr << "\n";
    }
    std::cout << "The value stored at address pointer is pointing to is: " << *ptr << "\n";
    return 0;
}