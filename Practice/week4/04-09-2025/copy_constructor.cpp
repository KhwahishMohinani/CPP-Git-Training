#include <iostream>

class Complex
{
    int x, y;

public:
    Complex()
    {
        x = 2;
        y = 1;
    }

    Complex(int a, int b)
    {
        x = a;
        y = b;
    }

    Complex(int b)
    {
        x = 3;
        y = b;
    }

    void print()
    {
        std::cout << "x = " << x << "\ny = " << y << "\n";
    }
};

int main()
{
    Complex c1{65};
    Complex c2(25, 72);
    Complex c3;
    Complex c4(c2);
    Complex c5(c3); // if we don't write copy constructor, compiler by default make it
    c4.print();
    c5.print();
}