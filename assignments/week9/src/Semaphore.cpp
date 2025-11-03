#include "Semaphore.h"

Semaphore::Semaphore(bool start)
    : permit(start)
{
}

void Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.wait(lock, [this]()
                            { return permit; });
    permit = false;
}

void Semaphore::signal()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        permit = true;
    }
    condition_variable.notify_one();
}
