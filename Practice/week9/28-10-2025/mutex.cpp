#include <iostream>
#include <thread>
#include <mutex>

int myAmount = 0;
std::mutex m;

void addMoney()
{
    m.lock();
    ++myAmount;
    m.unlock();
}

int main()
{
    std::thread t1(addMoney);
    std::thread t2(addMoney);
    std::thread t3(addMoney);

    t1.join();
    t2.join();
    t3.join();

    std::cout << myAmount << "\n";
}