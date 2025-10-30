#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void Worker1()
{
    while (true)
    {
        if (std::try_lock(m1, m2) == -1)
        {
            std::cout << "Worker1 got both locks\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            m1.unlock();
            m2.unlock();
            break;
        }
        else
        {
            std::cout << "Worker1 failed, retrying...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

void Worker2()
{
    while (true)
    {
        if (std::try_lock(m1, m2) == -1)
        {
            std::cout << "Worker2 got both locks\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            m1.unlock();
            m2.unlock();
            break;
        }
        else
        {
            std::cout << "Worker2 failed, retrying...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

int main()
{
    std::thread t1(Worker1);
    std::thread t2(Worker2);

    t1.join();
    t2.join();
}