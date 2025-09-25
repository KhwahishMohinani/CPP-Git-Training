#include <iostream>
#include <exception>

void myTerminateHandler()
{
    std::cout << "Custom terminate handler called\n";
}

int main()
{
    std::set_terminate(myTerminateHandler);
    throw 2;
}