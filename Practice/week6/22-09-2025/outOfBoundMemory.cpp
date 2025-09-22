#include <iostream>
using namespace std;

void fillArray(int *arr, int n)
{
    for (int i = 0; i <= n; ++i)
    {
        arr[i] = i * i;
    }
}

void printArray(int *arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n = 5;
    int *arr = new int[n];

    fillArray(arr, n);

    printArray(arr, n);

    delete[] arr;

    cout << "Trying to access arr[2] after delete: " << arr[2] << endl;

    return 0;
}
