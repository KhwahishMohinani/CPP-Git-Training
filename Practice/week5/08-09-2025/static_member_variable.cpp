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
};

int Account::roi = 2; // static member variable is defined outside the class but declared inside the class

int main()
{
    Account a, a2;
    std::cout << Account::getRoi() << "\n";
    std::cout << a.getRoi() << "\n";
    std::cout << a2.getRoi() << "\n";
}