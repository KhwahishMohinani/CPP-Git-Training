#include <iostream>

class Account
{
    int balance;

public:
    void setBalance(int b)
    {
        balance = b;
    }
    int getRoi()
    {
        return roi = roi + 1;
    }
    static int roi;
};

int Account::roi = 2;

int main()
{
    Account a, a2;
    std::cout << Account::roi << "\n"; // static data members can be accessed without an object
    std::cout << a.getRoi() << "\n";
    std::cout << a2.getRoi() << "\n";
}