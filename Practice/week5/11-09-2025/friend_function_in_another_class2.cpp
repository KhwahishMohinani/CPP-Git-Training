#include <iostream>

class A;

class B
{
private:
    int b = 9;

public:
    void func(A obj);
};

class A
{
private:
    int a = 2;

public:
    friend void B::func(A obj);
    int c;
};

void B::func(A obj)
{
    std::cout << obj.a << "\n";
}

int main()
{
    A a;
    B b;
    b.func(a);
}
