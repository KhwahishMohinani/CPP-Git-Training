#include <iostream>

int main()
{
    int x = 9;
    int *ptr = &x;
    std::cout << "Value of x is: " << x << "\n";
    std::cout << "Address of x is: " << &x << "\n";
    std::cout << "Value of ptr is: " << ptr << "\n";
    std::cout << "Value of *ptr is: " << *ptr << "\n";
    std::cout << "Value of &ptr is: " << &ptr << "\n";
    int y = 8.9;
    ptr = &y;
    std::cout << "Value of ptr is: " << ptr << "\n";
    std::cout << "Value of *ptr is: " << *ptr << "\n";
    *ptr = 3;
    std::cout << "Value of ptr is: " << ptr << "\n";
    std::cout << "Value of *ptr is: " << *ptr << "\n";
    std::cout << "Value of x is: " << y << "\n";
    return 0;
}