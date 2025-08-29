#include <iostream>

int func()
{
    return 5;
}

int main()
{
    int (*funcPtr)() = &func;
    void *vPtr = &func;
    return 0;
}