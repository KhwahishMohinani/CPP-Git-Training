#include <iostream>
#include <thread>
#include <chrono>

void run(int x)
{
    while (x-- > 0)
    {
        std::cout << x << "\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main()
{
    std::thread t(run, 10);
    std::cout << "Main()\n";
    t.join(); // if we don't join at all, our program will terminate
    // t.join(); // abort if joined two times
    std::cout << "main() after\n";
    return 0;
}