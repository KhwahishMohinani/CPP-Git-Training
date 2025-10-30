#include <iostream>
#include <chrono>
#include <thread>

void findOddSum(long &result)
{
    long sum = 0;
    for (long i = 0; i <= 1234567890; i++)
    {
        if (i % 2 != 0)
        {
            sum += i;
        }
    }
    result = sum;
}

void findEvenSum(long &result)
{
    long sum = 0;
    for (long i = 0; i <= 1234567890; i++)
    {
        if (i % 2 == 0)
        {
            sum += i;
        }
    }
    result = sum;
}

int main()
{
    long odd_sum = 0;
    long even_sum = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    std::thread t1(findOddSum, std::ref(odd_sum));
    std::thread t2(findEvenSum, std::ref(even_sum));

    t1.join();
    t2.join();

    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);

    std::cout << "Odd sum = " << odd_sum << "\n";
    std::cout << "Even sum = " << even_sum << "\n";
    std::cout << "Time taken = " << duration.count() / 1000000.0 << " seconds\n";
}
