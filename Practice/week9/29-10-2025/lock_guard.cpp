#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
int buffer = 0;

void func(char c, int loopFor)
{
    // std::lock_guard<std::mutex> lock(m1);
    for (int i = 0; i < loopFor; i++)
    {
        std::lock_guard<std::mutex> lock(m1); // automatically unlocks if goes out of scope
        std::cout << "Thread id: " << c << " -> " << ++buffer << "\n";
    }
}

int main()
{
    std::thread t1(func, '1', 10);
    std::thread t2(func, '2', 10);
    t1.join();
    t2.join();
}