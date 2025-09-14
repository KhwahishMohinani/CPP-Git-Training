#include <iostream>
#include "../include/IBank.h"
#include "../include/Bank.h"
#include "../include/IAccount.h"
#include "../include/User.h"

int main()
{
    User user;
    IBank *iBankPtr = new Bank();
    std::string type;

    while (true)
    {
        std::cout << "1. Signup\n2. Login\n3. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            std::cout << "Signup as (customer/admin): ";
            std::cin >> type;
            iBankPtr->addUser(type);
        }
        else if (choice == 2)
        {
            User *loggedIn = user.login(*iBankPtr);
            if (loggedIn)
            {
                std::cout << "Login successful!\n";
                type = loggedIn->getType();
                if (type == "customer")
                {
                    loggedIn->showMenu(*iBankPtr);
                }
                else if (type == "admin")
                {
                    loggedIn->showMenu(*iBankPtr);
                }
            }
            else
            {
                std::cout << "Login failed!\n";
            }
        }
        else
        {
            break;
        }
    }
}
