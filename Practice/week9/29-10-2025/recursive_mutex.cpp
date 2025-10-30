#include <iostream>
#include <thread>
#include <mutex>

// std::mutex m1;  // This will cause deadlock
std::recursive_mutex m1;
int buffer = 0;

void recursive_mutex(char c, int loopFor)
{
    if (loopFor < 0)
        return;

    m1.lock();
    std::cout << "Thread id: " << c << " -> " << buffer++ << "\n";
    recursive_mutex(c, --loopFor);
    m1.unlock();
}

int main()
{
    std::thread t1(recursive_mutex, '1', 10);
    std::thread t2(recursive_mutex, '2', 10);
    t1.join();
    t2.join();
}