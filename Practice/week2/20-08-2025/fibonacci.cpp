#include <vector>
#include "fibonacci.h"

extern "C" int fibonacci_series(int num)
{
    std::vector<int> arr(num + 1);
    arr[0] = 0;
    arr[1] = 1;
    for (int i = 2; i <= num; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    return arr[num];
}