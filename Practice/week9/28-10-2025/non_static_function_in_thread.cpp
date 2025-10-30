#include <iostream>
#include <thread>

class Base
{
public:
    void run(int x)
    {
        while (x-- > 0)
        {
            std::cout << x << "\n";
        }
    }
};

int main()
{
    Base b;
    std::thread t(&Base::run, &b, 10);
    t.join();
    return 0;
}