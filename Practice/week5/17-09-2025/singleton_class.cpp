#include <iostream>

class Singleton
{
    Singleton()
    {
        std::cout << "Singleton constructor created\n";
    }

    Singleton(const Singleton &) = delete;
    Singleton operator=(const Singleton &) = delete;

public:
    static Singleton &getInstance()
    {
        static Singleton instance;
        return instance;
    }

    void print()
    {
        std::cout << "Print function\n";
    }
};

int main()
{
    Singleton &instance1 = Singleton::getInstance(); // error if instance is not reference
    instance1.print();
    Singleton &instance2 = Singleton::getInstance();
    instance2.print();

    std::cout << &instance1 << "\n"
              << &instance2 << "\n"; // both instances have same address

    instance1.print();
}