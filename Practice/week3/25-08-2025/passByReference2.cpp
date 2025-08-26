#include <iostream>

void printVal(double d)
{
    std::cout << d << '\n';
}

void printRef(const double &d)
{
    std::cout << d << '\n';
}

void printStr(std::string &s)
{
    std::cout << s << '\n';
}

int main()
{
    printVal(5); // 5 converted to temporary double, copied to parameter d
    printRef(5); // 5 converted to temporary double, bound to parameter d
    std::string s = "Hello";
    printStr(s);
    std::cout << sizeof(void *) << "\n";
    std::cout << sizeof(int) << "\n";
    return 0;
}