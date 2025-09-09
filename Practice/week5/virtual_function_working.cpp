#include <iostream>

class Parent
{
    int x;

public:
    virtual void f1()
    {
        std::cout << "F1 from base\n";
    }
    // virtual void f2(); // Error because defined but not declared
    virtual void f3()
    {
        std::cout << "F3 from base\n";
    }
};

class Child : public Parent
{
    void f1()
    {
        std::cout << "F1 from derived\n";
    }
    void f2()
    {
        std::cout << "F2 from derived\n";
    }
};

int main()
{
    Parent *ptr, p;
    ptr = &p; // parent class pointer pointing to parent class object
    ptr->f1();
    // ptr->f2();

    Parent *ptr2;
    Child c;
    ptr2 = &c;
    ptr2->f1();
    ptr2->f3();
    std::cout << sizeof(Parent) << "\n";
}