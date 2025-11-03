#ifndef I_SEMAPHORE_H
#define I_SEMAPHORE_H

class ISemaphore
{
public:
    virtual void wait() = 0;
    virtual void signal() = 0;
};

#endif
