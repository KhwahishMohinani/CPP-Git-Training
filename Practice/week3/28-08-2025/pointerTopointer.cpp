#include <iostream>

int main()
{
    int n = 9;
    int *ptr = &n;
    int **ptrptr = &ptr;

    std::cout << "n = " << n << "\n";
    std::cout << "*ptr = " << *ptr << "\n";
    std::cout << "**ptrptr = " << **ptrptr << "\n";
    std::cout << "ptr = " << ptr << "\n";
    std::cout << "*ptrptr " << *ptrptr << "\n";
    std::cout << "ptrptr = " << ptrptr << "\n";
}