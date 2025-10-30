#include <iostream>
#include <thread>
#include <chrono>

void run(int x)
{
    while (x > 0)
    {
        std::cout << x << "\n";
        x--;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main()
{
    std::thread t(run, 10);
    std::cout << "Main()\n";
    t.detach();
    std::cout << "main() after\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}