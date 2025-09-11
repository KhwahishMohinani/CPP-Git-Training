#include <iostream>

class Complex
{
    int a, b;

public:
    void setData(int x, int y)
    {
        a = x;
        b = y;
    }
    void showData()
    {
        std::cout << "a = " << a << "\n";
        std::cout << "b = " << b << "\n";
    }
    std::istream &operator>>(std::istream &din, Complex &c1)
    {
        din >> c1.a >> c1.b;
        return din;
    }
    std::ostream &operator<<(std::ostream &dout, Complex &c1)
    {
        dout << "a = " << c1.a << "\nb = " << c1.b << "\n";
        return dout;
    }
};

int main()
{
    Complex c1;
    std::cout << "Enter a complex number: ";
    std::cin >> c1;
    std::cout << c1;
}

/*
When you write an operator as a member, the left-hand operand (LHS) must be an object of that class.
Now think about <<:
std::cout << obj;
This really calls:
operator<<(std::cout, obj);
The LHS (std::cout) is an std::ostream, not your class.
If you tried to make operator<< a member of your class, it would look like:
class MyClass {
    void operator<<(std::ostream& os); // wrong!
};
Then you would have to call it like:
obj << std::cout; // (reversed order)
That’s why we need operator<< to be a free function (not inside your class) where the first parameter is std::ostream&.
*/