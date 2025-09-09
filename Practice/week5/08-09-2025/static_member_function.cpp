#include <iostream>

class Account
{
    int balance;
    static int roi;

public:
    void setBalance(int b)
    {
        balance = b;
    }
    int getRoi()
    {
        return roi = roi + 1;
    }
    static void setRoi(int r) // can only access static data members
    {
        roi = r;
        // balance = 3;//cannot access
    }
};

int Account::roi = 2;

int main()
{
    Account a, a2;
    Account::setRoi(4); // static member functions can be accessed without an object
    std::cout << a.getRoi() << "\n";
    std::cout << a2.getRoi() << "\n";
}