#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class BinarySemaphore
{
    bool available;
    std::mutex m;
    std::condition_variable cv;

public:
    BinarySemaphore(bool init = false) : available(init)
    {
    }
    void acquire()
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&]
                { return available; });
        available = false;
    }
    void release()
    {
        {
            std::lock_guard<std::mutex> lock(m);
            available = true;
        }
        cv.notify_one();
    }
};

BinarySemaphore sem(false);

void producer()
{
    std::cout << "Producing data...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Data ready!\n";
    sem.release();
}

void consumer()
{
    std::cout << "Waiting for data...\n";
    sem.acquire();
    std::cout << "Consuming data!\n";
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}