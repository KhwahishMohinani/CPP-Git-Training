#include <iostream>

void printStringByValue(std::string s)
{
    std::cout << s << "\n";
}

void printStringByAddress(std::string *ptr)
{
    std::cout << *ptr << "\n";
}

int main()
{
    std::string s = "hello";
    printStringByValue(s);
    printStringByAddress(&s);
    return 0;
}