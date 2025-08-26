#include <iostream>

int main()
{
    int x = 5;
    const int *ptr = &x;
    // *ptr = 5; //not allowed
    std::cout << "Value of x is: " << x << "\n";
    std::cout << "Value of *ptr is: " << *ptr << "\n";

    x = 6;
    std::cout << "Value of x is: " << x << "\n";
    std::cout << "Value of *ptr is: " << *ptr << "\n";

    const int y = 2;
    ptr = &y;
    std::cout << "Value of x is: " << x << "\n";
    std::cout << "Value of *ptr is: " << *ptr << "\n";

    return 0;
}