#include <iostream>
using std::cout;

struct Base
{
    virtual void fun() { cout << "Base\n"; }
};
struct Derived : Base
{
    void fun() { cout << "Derived\n"; }
};

void test(Base b) { b.fun(); }
void test(Base *b) { b->fun(); }

int main()

{
    Derived d;
    test(d);
    return 0;
}