#include <iostream>

int main()
{
    int x = 8;
    int *ptr{};
    std::cout << "The value of ptr is: " << ptr << "\n";
    // std::cout << "The value of *ptr is: " << *ptr << "\n";  //segmentation fault because it is not pointing to anything

    ptr = &x;
    std::cout << "The value of ptr is: " << ptr << "\n";
    std::cout << "The value of *ptr is: " << *ptr << "\n";

    ptr = NULL;
    std::cout << "The value of ptr is: " << ptr << "\n";
    // std::cout << "The value of *ptr is: " << *ptr << "\n";

    ptr = nullptr;
    std::cout << "The value of ptr is: " << ptr << "\n";
    // std::cout << "The value of *ptr is: " << *ptr << "\n";

    ptr = 0;
    std::cout << "The value of ptr is: " << ptr << "\n";
    std::cout << "The value of *ptr is: " << *ptr << "\n";

    return 0;
}