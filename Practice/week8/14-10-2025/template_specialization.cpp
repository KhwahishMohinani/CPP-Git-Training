#include <iostream>

template <typename T>
class Print
{
public:
    Print(T data)
    {
        std::cout << "General template for " << data << "\n";
    }
};

template <>
class Print<char *>
{
public:
    Print(char *data)
    {
        std::cout << "Specialized template for " << data << "\n";
    }
};

int main()
{
    Print<int> print1(4);
    Print print3("bottle"); // T = const char* (deduced automatically)
    Print<char *> print2("water");
}