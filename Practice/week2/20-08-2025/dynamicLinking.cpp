#include <iostream>
#include "findMaxElement.h"

int main()
{
    int arr[8] = {3, 76, 43, 21, 82, 29, 59, 80};
    std::cout << "Highest Element of array is: " << findMax(arr, 8) << "\n";
    return 0;
}