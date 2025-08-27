#include <iostream>

const std::string &func(const std::string &s)
{
    return s;
}

std::string getHello()
{
    return "Hello";
}

int main()
{
    std::string s = func(getHello());
    std::cout << s;
}