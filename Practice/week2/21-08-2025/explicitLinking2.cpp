#include <iostream>
#include <dlfcn.h>

void operations(int num1, int num2)
{
    void *handle = dlopen("./libadd.so", RTLD_NOW);
    if (!handle)
    {
        std::cerr << "Cannot load library " << dlerror() << "\n";
        return;
    }

    int (*addition)(int, int) = (int (*)(int, int))dlsym(handle, "add");
    const char *error = dlerror();
    if (error)
    {
        std::cerr << "Cannot find symbol 'add' " << error << "\n";
        dlclose(handle);
        return;
    }
    std::cout << "The addition of the numbers is : " << addition(num1, num2) << "\n";

    int (*subtraction)(int, int) = (int (*)(int, int))dlsym(handle, "subtract");
    error = dlerror();
    if (error)
    {
        std::cerr << "Cannot find symbol 'subtract' " << error << "\n";
        dlclose(handle);
        return;
    }
    std::cout << "The subtraction of the numbers is : " << subtraction(num1, num2) << "\n";
    dlclose(handle);
    return;
}

int main()
{
    int num1, num2;
    std::cout << "Enter two numbers: ";
    std::cin >> num1 >> num2;
    operations(num1, num2);
    return 0;
}