#include <iostream>

int main()
{
    int a = 7;
    const int &b = a;

    std::cout << "The value of a is: " << a << "\n";
    std::cout << "The value of b is: " << b << "\n";

    // b = 8;  //not allowed

    a = 8;
    std::cout << "The value of a is: " << a << "\n";
    std::cout << "The value of b is: " << b << "\n";
    return 0;
}