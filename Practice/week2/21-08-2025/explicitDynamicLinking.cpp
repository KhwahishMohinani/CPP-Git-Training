#include <iostream>
#include <dlfcn.h>

int main()
{
    void *handle = dlopen("./libprime.so", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << "Cannot Load library: " << dlerror() << "\n";
        return 1;
    }

    typedef bool (*isPrime_t)(int);
    isPrime_t isPrime = (isPrime_t)dlsym(handle, "isPrime");

    const char *error = dlerror();
    if (error)
    {
        std::cerr << "Couldn't load symbol isPrime " << error << "\n";
        dlclose(handle);
        return 1;
    }

    int num = 7;
    if (isPrime(num))
        std::cout << num << " is a Prime number\n";
    else
        std::cout << num << " is not a Prime number\n";

    dlclose(handle);

    return 0;
}