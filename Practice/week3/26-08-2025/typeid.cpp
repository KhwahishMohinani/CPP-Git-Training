#include <iostream>
#include <typeinfo>

int main()
{
    int x = 7;
    int *ptr = &x;
    std::cout << typeid(x).name() << "\n";
    std::cout << typeid(&x).name() << "\n";
    std::cout << typeid(ptr).name() << "\n";
    std::cout << typeid(*ptr).name() << "\n";
    std::cout << typeid(&ptr).name() << "\n";
    return 0;
}