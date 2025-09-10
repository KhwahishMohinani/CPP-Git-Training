#include <iostream>

class B;

class A
{
private:
    int a = 2;

public:
    friend void func(A, B);
    int c;
};

class B
{
private:
    int b = 9;

public:
    friend void func(A, B);
};

void func(A o1, B o2)
{
    std::cout << "Sum is: " << o1.a + o2.b << "\n";
}

int main()
{
    A obj1;
    B obj2;
    func(obj1, obj2);
}