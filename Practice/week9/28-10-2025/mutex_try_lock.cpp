#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void increaseCounter()
{
    for (int i = 0; i < 100000; i++)
    {
        if (mtx.try_lock())
        {
            ++counter;
            mtx.unlock();
        }
    }
}

int main()
{
    std::thread t1(increaseCounter);
    std::thread t2(increaseCounter);
    std::thread t3(increaseCounter);

    t1.join();
    t2.join();
    t3.join();

    std::cout << counter << "\n";
}
