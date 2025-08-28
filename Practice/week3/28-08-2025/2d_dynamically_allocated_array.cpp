#include <iostream>

int main()
{
    int x = 7;
    int a = 2;
    int **arr = new int *[x];
    for (int count = 0; count < x; count++)
    {
        arr[count] = new int[5];
    }
    arr[0][0] = 42;
    arr[4][1] = 34;
    std::cout << arr[0][0] << "\n";
    std::cout << arr[4][1] << "\n";
    for (int count = 0; count < x; count++)
    {
        delete[] arr[count];
    }

    delete[] arr;
}
