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

    /*Complex(Complex c)
    {
        x = 9;
        y = 8;
    }*/
    /*The compiler tries to call Complex(Complex c).
      But to pass c2 into this function by value, it needs to make a copy of c2.
      But making a copy of c2 itself requires calling the copy constructor again.
      Which calls the copy constructor again… and again… infinite recursion.*/

    Complex(Complex &c)
    {
        x = 9;
        y = 8;
        c.x = x;
        c.y = y;
    }
    void print()
    {
        std::cout << "x = " << x << "\ny = " << y << "\n";
    }
};

int main()
{
    Complex c1{65, 84};
    Complex c2(25, 72);
    c2.print();
    Complex c3;
    Complex c4(c2);

    c4.print();
    c2.print();
}