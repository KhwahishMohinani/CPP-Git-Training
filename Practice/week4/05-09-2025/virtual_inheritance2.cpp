#include <iostream>

class A
{
public:
    A() { std::cout << "A constructed\n"; }
};

class B : virtual public A
{
public:
    B() { std::cout << "B constructed\n"; }
};

class C : virtual public A
{
public:
    C() { std::cout << "C constructed\n"; }
};

class D : public B, public C
{
public:
    D() { std::cout << "D constructed\n"; }
};

int main()
{
    D d;
}

/*
This would be the output if we don't write virtual
A constructed
B constructed
A constructed
C constructed
D constructed
*/