#include <iostream>
#include <dlfcn.h>

void callLibrary(int n)
{
    void *handle = dlopen("../20-08-2025/libfibonacci.so", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << "Cannot load file " << dlerror() << "\n";
        return;
    }

    int (*fibonacci)(int) = (int (*)(int))dlsym(handle, "fibonacci_series");
    if (dlerror())
    {
        std::cerr << "Cannot load symbol 'fibonacci_series' " << dlerror() << "\n";
        return;
    }
    std::cout << "The fibonacci series for the term " << n << " is : " << fibonacci(n) << "\n";

    dlclose(handle);
}

int main()
{
    int n;
    std::cout << "Enter a number: ";
    std::cin >> n;

    callLibrary(n);
}