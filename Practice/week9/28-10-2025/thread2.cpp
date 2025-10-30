#include <iostream>
#include <chrono>
#include <thread>

long findOddSum()
{
    long sum = 0;
    for (long i = 0; i <= 1234567890; i++)
    {
        if (i % 2 != 0)
        {
            sum += i;
        }
    }
    return sum;
}

long findEvenSum()
{
    long sum = 0;
    for (long i = 0; i <= 1234567890; i++)
    {
        if (i % 2 == 0)
        {
            sum += i;
        }
    }
    return sum;
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    long odd_sum = std::thread t1(findOddSum);
    long even_sum = std::thread t2(findEvenSum);

    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
    std::cout << duration.count() / 1000000 << "\n";

    std::cout << "Odd sum = " << odd_sum << "\n";
    std::cout << "Even sum = " << even_sum << "\n";
}