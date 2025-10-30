#include <iostream>
#include <thread>

int main()
{
    auto fun = [](int x)
    {
        while (x-- > 0)
        {
            std::cout << x << "\n";
        }
    };
    std::thread t(fun, 10);
    t.join();
    return 0;
}