#include <iostream>

int &getX()
{
    int x = 9;
    return x;
}

int main()
{
    int &ref = getX(); // will not work
    std::cout << "The value of the reference is: " << ref << "\n";
    return 0;
}