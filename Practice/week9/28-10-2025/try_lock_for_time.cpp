#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

/*int amount = 0;
std::timed_mutex m;

void increment(int i)
{
    if (m.try_lock_for(std::chrono::seconds(1)))
    {
        ++amount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Thread " << i << " entered\n";
        m.unlock();
    }
    else
    {
        std::cout << "Thread " << i << " couldn't enter\n";
    }
}

int main()
{
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    std::cout << "amount: " << amount << "\n";
}
*/

int amount = 0;
std::timed_mutex m;

void increment(int i)
{
    if (m.try_lock_for(std::chrono::seconds(2)))
    {
        ++amount;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Thread " << i << " entered\n";
        m.unlock();
    }
    else
    {
        std::cout << "Thread " << i << " couldn't enter\n";
    }
}

int main()
{
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    std::cout << "amount: " << amount << "\n";
}