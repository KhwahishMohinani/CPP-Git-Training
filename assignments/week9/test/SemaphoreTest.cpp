#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include "Semaphore.h"

class SemaphoreTest : public ::testing::Test
{
protected:
    Semaphore semaphore;
};

TEST_F(SemaphoreTest, GivenPermitTrue_WhenWaitCalled_ThenShouldNotBlock)
{
    Semaphore semaphore1(true);

    auto start = std::chrono::steady_clock::now();
    semaphore1.wait();
    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(duration, 50);
}

TEST_F(SemaphoreTest, GivenPermitFalse_WhenWaitCalled_ThenShouldBlockUntilSignal)
{
    bool taskCompleted = false;

    std::thread thread([&]()
                       {
        semaphore.wait();
        taskCompleted = true; });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_FALSE(taskCompleted);

    semaphore.signal();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    EXPECT_TRUE(taskCompleted);
    thread.join();
}

TEST_F(SemaphoreTest, GivenMultipleSignals_WhenWaitCalled_ThenShouldWorkOnlyOncePerSignal)
{
    bool firstTaskDone = false;
    bool secondTaskDone = false;

    std::thread thread1([&]()
                        {
        semaphore.wait();
        firstTaskDone = true; });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_FALSE(firstTaskDone);

    semaphore.signal();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_TRUE(firstTaskDone);

    std::thread thread2([&]()
                        {
        semaphore.wait();
        secondTaskDone = true; });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_FALSE(secondTaskDone);

    semaphore.signal();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_TRUE(secondTaskDone);

    thread1.join();
    thread2.join();
}

TEST_F(SemaphoreTest, GivenMultipleThreadsWaiting_WhenSignalCalled_ThenOnlyOneProceeds)
{
    bool thread1Done = false;
    bool thread2Done = false;

    std::thread thread1([&]()
                        {
        semaphore.wait();
        thread1Done = true; });

    std::thread thread2([&]()
                        {
        semaphore.wait();
        thread2Done = true; });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_FALSE(thread1Done);
    EXPECT_FALSE(thread2Done);

    semaphore.signal();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_NE(thread1Done, thread2Done);

    semaphore.signal();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_TRUE(thread1Done);
    EXPECT_TRUE(thread2Done);

    thread1.join();
    thread2.join();
}
