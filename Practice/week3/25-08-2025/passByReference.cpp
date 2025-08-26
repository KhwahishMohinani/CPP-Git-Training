#include <iostream>

void printX(double val, double &ref)
{
    std::cout << "The value of val is: " << val << "\n";
    std::cout << "The address of val is: " << &val << "\n";
    std::cout << "The value of ref is: " << ref << "\n";
    std::cout << "The address of ref is: " << &ref << "\n";
}

int main()
{
    double x = 8;
    std::cout << "In main, The value of x is: " << x << "\n";
    std::cout << "In main, The address of x is: " << &x << "\n";
    printX(x, x);
    return 0;
}