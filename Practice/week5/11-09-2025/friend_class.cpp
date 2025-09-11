#include <iostream>

class A
{
private:
    int a = 2;

public:
    friend class B;
    int c;
};

class B
{
private:
    int b = 9;

public:
    void func(A obj)
    {
        std::cout << obj.a << "\n";
    }
};

int main()
{
    A a;
    B b;
    b.func(a);
}
