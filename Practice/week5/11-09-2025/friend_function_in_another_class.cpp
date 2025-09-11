#include <iostream>

class B;

class A
{
private:
    int a = 2;

public:
    friend void B::func(A obj);
    /*
    At the point where you write friend void B::func(A obj);,
    the compiler only knows class B; exists, but it doesn’t know anything about its member functions yet.
    So when you try to say "make B::func(A obj) a friend", the compiler complains:
    error: invalid use of incomplete type ‘class B’
    */
    int c;
};

class B
{
private:
    int b = 9;

public:
    void func(A obj)
    {
        std::cout << obj.a;
    }
};

int main()
{
    A a;
    B b;
    b.func(a);
}
