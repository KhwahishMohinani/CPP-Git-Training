#include <iostream>
#include "../include/Admin.h"

Admin::Admin(int userId, std::string password, std::string type)
{
    setUserId(userId);
    setPassword(password);
    setType(type);
}

void Admin::createAccount(IBank &bank)
{
    bank.addAccount(this);
}

void Admin::closeAccount(IBank &bank, IAccount *account)
{
    bank.removeAccount(account);
}

void Admin::showMenu(IBank &bank)
{
    int choice;
    do
    {
        std::cout << "1. Create Account\n2. Close Account\n3. Create User\n4. Delete User\n5. Show all accounts\n6. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount(bank);
            break;
        case 2:
        {
            std::cout << "Enter Account number: ";
            long accountNumber;
            std::cin >> accountNumber;
            IAccount *account = bank.getAccountByAccountNumber(accountNumber);
            if (!account)
                std::cout << "Account not found\n";
            else
            {
                closeAccount(bank, account);
            }
            break;
        }
        case 3:
        {
            std::string type;
            std::cout << "Signup as (customer/admin): ";
            std::cin >> type;
            bank.addUser(type);
            break;
        }
        case 4:
            bank.removeUser();
            break;
        case 5:
            bank.showAllAccounts();
            break;
        case 6:
            std::cout << "Logging out\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}
