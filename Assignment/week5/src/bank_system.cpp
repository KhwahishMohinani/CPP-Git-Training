#include <iostream>
#include "../include/IBank.h"
#include "../include/Bank.h"
#include "../include/User.h"

void showCustomerMenu(IBank &bank, User *loggedIn)
{
    int choice;
    do
    {
        std::cout << "1. Create new Account\n2. Access Existing Account\n3. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            bank.addAccount(loggedIn);
            break;
        case 2:
            std::cout << "Enter Account number: ";
            long accountNumber;
            std::cin >> accountNumber;
            break;
        case 3:
            std::cout << "Logging out\n";
            break;
        default:
            std::cout << "Invalid choice. Try again\n";
            break;
        }
    } while (choice != 3);
}

void showAdminMenu()
{
}

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
                    showCustomerMenu(*iBankPtr, loggedIn);
                }
                else if (type == "admin")
                {
                    showAdminMenu();
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
