#include <iostream>

int main()
{
    int a = 8;
    {
        int &b = a;
        std::cout << "The value of reference is: " << b << "\n";
    }
    // std::cout << "The value of reference is: " << b << "\n"; //it will show error
    std::cout << "The value of reference is: " << a << "\n";
    return 0;
}