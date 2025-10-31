#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

std::binary_semaphore sem(0);

void producer()
{
    std::cout << "Producing data\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Data ready\n";
    sem.release();
}

void consumer()
{
    std::cout << "Waiting for data\n";
    sem.acquire();
    std::cout << "Consuming data\n";
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}