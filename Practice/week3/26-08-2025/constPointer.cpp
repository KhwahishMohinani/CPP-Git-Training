#include <iostream>

int main()
{
    int x = 5;
    int *const ptr = &x; // can't be intitialized again
    int y = 9;
    // ptr = &y; // not allowed
    *ptr = 6;
    x = 3;
    std::cout << *ptr << "\n";
    return 0;
}