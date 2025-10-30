#include <iostream>
#include <thread>

static bool is_finished = false;

void DoWork()
{
    while (!is_finished)
    {
        std::cout << "Working...\n";
    }
}

int main()
{
    std::thread worker(DoWork);
    std::cin.get();
    is_finished = true;
    worker.join();
    std::cout << "Finished\n";
    std::cin.get();
}