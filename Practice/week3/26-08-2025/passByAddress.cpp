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
    // printStringByAddress(&"hello");  //can't take the address of rvalue
    return 0;
}