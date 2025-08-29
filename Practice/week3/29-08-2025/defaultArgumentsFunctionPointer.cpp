#include <iostream>

void func(int x)
{
    std::cout << "Value of x is: " << x << "\n";
}

void func(int x, int y = 9)
{
    std::cout << "Value of x is: " << x << "\n";
    std::cout << "Value of y is: " << y << "\n";
}

int main()
{
    void (*f1)(int) = func; // for overloading either we can use functions like these to tell how many argument function we want
    f1(3);

    (static_cast<void (*)(int, int)>(func))(6, 8); // or we can do this
    return 0;
}
