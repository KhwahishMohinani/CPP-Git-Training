#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    int *arr = new int[n];
    arr[0] = 6;
    delete[] arr;

    arr = new int[3]{8, 0, 3};
    std::cout << *arr << "\n"; // print first element
    delete[] arr;
    return 0;
}