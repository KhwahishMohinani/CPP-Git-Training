#ifndef MOCK_SEMAPHORE_H
#define MOCK_SEMAPHORE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Semaphore.h"

class MockSemaphore : public ISemaphore
{
public:
    MOCK_METHOD(void, wait, ());
    MOCK_METHOD(void, signal, ());
};

#endif
