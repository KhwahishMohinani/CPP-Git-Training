#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
int balance = 0;

void add_money(int money)
{
    std::lock_guard<std::mutex> lg(m);
    balance += money;
    std::cout << "Amount " << money << " added successfully. New Balance: " << balance << "\n";
    cv.notify_one();
}

void withdraw_money(int money)
{
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, []
            { return (balance != 0) ? true : false; });
    if (balance >= money)
    {
        balance -= money;
        std::cout << "Amount " << money << " deducted successfully. New Balance: " << balance << "\n";
    }
    else
    {
        std::cout << "Amount can't be deducted. Current balance is less than " << money << "\n";
    }
}

int main()
{
    std::thread t1(withdraw_money, 500);
    std::thread t2(add_money, 500);
    t1.join();
    t2.join();
}