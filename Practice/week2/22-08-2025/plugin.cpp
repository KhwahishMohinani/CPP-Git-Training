#include <iostream>

extern "C" void printCore();

extern "C" void printPlugin()
{
    std::cout << "This is plugin function\n";
    printCore();
}