#include <iostream>
using namespace std;

void corruptArray(int *arr1, int *arr2, int n)
{
    for (int i = 0; i <= n; ++i)
    {
        arr1[i] = i * 10;
        arr2[i] = i * 20;
    }
}

int main()
{
    int n = 5;

    int *arr1 = new int[n];
    int *arr2 = new int[n];

    corruptArray(arr1, arr2, n);

    cout << "arr1: ";
    for (int i = 0; i < n; ++i)
        cout << arr1[i] << " ";
    cout << endl;

    cout << "arr2: ";
    for (int i = 0; i < n; ++i)
        cout << arr2[i] << " ";
    cout << endl;

    delete[] arr1;

    arr2 = arr1;
    delete[] arr2;

    cout << "arr1[2] = " << arr1[2] << endl;

    return 0;
}
