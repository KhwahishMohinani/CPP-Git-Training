#include <iostream>

std::string &getProgramName()
{
    static std::string s = "Calculator\n"; // if i don't write static i will get an error because a dangling reference would be there
    return s;
}

std::string &printHello()
{
    std::string s = "Hello\n";
    return s;
}

int main()
{
    std::cout << "The program name is: " << getProgramName();
    /*std::string str = printHello(); // dangling reference (if i assign it to str variable, it will have undefined behaviour)
    std::cout << str;*/
}