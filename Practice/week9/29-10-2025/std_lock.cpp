#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void task1()
{
    std::lock(m1, m2);
    std::cout << "Thread 1 acquired both locks\n";
    m1.unlock();
    m2.unlock();
}

void task2()
{
    std::lock(m2, m1);
    std::cout << "Thread 2 acquired both locks\n";
    m2.unlock();
    m1.unlock();
}

int main()
{
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();
}
