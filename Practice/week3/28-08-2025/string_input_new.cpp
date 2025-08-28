#include <iostream>
#include <algorithm>

int main()
{
    int n;
    std::cout << "How many names would you like to enter?\n";
    std::cin >> n;
    std::string *arr = new std::string[n];
    for (int i = 1; i <= n; i++)
    {
        std::cout << "Enter name #" << i << " ";
        std::cin >> arr[i - 1];
    }
    std::sort(arr, arr + n);
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << "\t";
    }
    std::cout << "\n";

    delete[] arr;
    return 0;
}