#include <iostream>

class A
{
private:
    int a = 2;

public:
    friend class B;
    /*
    You’re not talking about any member functions at all.
    You’re saying: “Whoever class B is, once it’s fully defined, it will be granted full friendship.”
    The compiler doesn’t need to know yet what members B has, because it’s not checking signatures — it’s just recording a relationship:
    “A trusts B (all of it)”.
    When B is later defined, all its member functions automatically gain access.
    So no forward-declaration problem arises here.
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
        std::cout << obj.a << "\n";
    }
};

int main()
{
    A a;
    B b;
    b.func(a);
}
