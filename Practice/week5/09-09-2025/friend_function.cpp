#include <iostream>

class Complex
{
    int a;

public:
    int getData()
    {
        return a;
    }
    void setData(int x)
    {
        a = x;
    }
    friend int fun(Complex);
};

int fun(Complex c)
{
    std::cout << "inside friend function\n";
    // return a; //this will generate error because friend function cannot directly access data members of that class
    return c.a;
}

int main()
{
    Complex c;
    std::cout << fun(c) << "\n";
    c.setData(8);
    std::cout << fun(c) << "\n";
}