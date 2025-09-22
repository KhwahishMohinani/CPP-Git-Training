#include <iostream>

int get_sum()
{
    return 0;
}

int sum_digits(int n)
{
    int sum = get_sum();
    while (n > 0)
    {
        int rem = n % 10;
        sum += rem;
        n = n / 10;
    }
    return sum;
}

int sum_factors(int n)
{
    int sum = get_sum();
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }
    return sum;
}

int main()
{
    int num = 60;
    std::cout << "Sum of factors: " << sum_factors(num) << "\n";
    std::cout << "Sum of digits: " << sum_digits(num) << "\n";
}