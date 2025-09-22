#include <iostream>
using namespace std;

int compute(int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i <= n; ++i)
    {
        sum += arr[i];
    }
    return sum;
}

int main()
{
    int n = 5;
    int *arr = new int[n];

    for (int i = 0; i < n; ++i)
    {
        arr[i] = i + 1;
    }

    delete[] arr;
    arr = nullptr;
    std::cout << *arr << "\n";
    int result = compute(arr, n);
    cout << "Sum = " << result << endl;

    return 0;
}
