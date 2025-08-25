#include <iostream>
#include <dlfcn.h>

void printCore()
{
    std::cout << "This printCore function is in main file\n";
}

int main()
{
    printCore();
    void *handle = dlopen("./libcore.so", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << "Cannot open file " << dlerror() << "\n";
        return 1;
    }
    void (*printCore)(void) = (void (*)(void))dlsym(handle, "printCore");
    const char *error = dlerror();
    if (error)
    {
        std::cerr << "Cannot load symbol 'printCore' " << error << "\n";
        dlclose(handle);
        return 1;
    }
    printCore();
    dlclose(handle);
    printCore();
    return 0;
}