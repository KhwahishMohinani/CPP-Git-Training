#include <iostream>

int main()
{
    int a = 8;
    int &b = a;
    std::cout << "Value of a is: " << b << "\n";
    int g = 0;

    double d{2};
    double &c = d;

    // int &e = d; // This will not compile due to wrong reference type
    int &f = a;
    f = 1;
    std::cout << "Value of a is: " << a << "\n";
    f = g;
    std::cout << "Value of a is: " << a << "\n";

    //&f = g;  //cannot reference any other variable
}