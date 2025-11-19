#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "ISemaphore.h"
#include <mutex>
#include <condition_variable>

class Semaphore : public ISemaphore
{
private:
    bool permit;
    std::mutex mutex;
    std::condition_variable condition_variable;

public:
    Semaphore(bool start = false);
    void wait();
    void signal();
};

#endif
