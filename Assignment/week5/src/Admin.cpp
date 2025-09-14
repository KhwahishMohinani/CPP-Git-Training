#include <iostream>
#include "../include/Admin.h"
#include "../include/InputHandler.h"

Admin::Admin(int userId, std::string password, std::string type)
{
    setUserId(userId);
    setPassword(password);
    setType(type);
}

void Admin::createAccount(IBank &bank)
{
    int customerId;
    std::cout << "Enter Customer ID to create an account for: ";
    std::cin >> customerId;

    User *user = bank.findUserById(customerId);

    if (user == nullptr)
    {
        std::cout << "Error: No user found with ID " << customerId << "\n";
    }
    else if (user->getType() != "customer")
    {
        std::cout << "Error: User with ID " << customerId << " is not a customer!\n";
    }
    else
    {
        bank.addAccount(user);
    }
}

void Admin::closeAccount(IBank &bank)
{
    InputHandler inputHandler;
    std::string input;
    long accountNumber, longValue;
    std::cout << "Enter Account number: ";
    while (true)
    {
        std::cin >> input;
        if (inputHandler.isValidLong(input, longValue))
        {
            accountNumber = longValue;
            break;
        }
        else
        {
            std::cout << "Please enter the correct account number\n";
        }
    }
    IAccount *account = bank.getAccountByAccountNumber(accountNumber);
    if (!account)
        std::cout << "Account not found\n";
    else
    {
        bank.removeAccount(account);
    }
}

void Admin::showMenu(IBank &bank)
{
    InputHandler inputHandler;
    int choice, value;
    std::string input;
    do
    {
        std::cout << "1. Create Account\n2. Close Account\n3. Create User\n4. Delete User\n5. Show all accounts\n6. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> input;
        if (inputHandler.isValidInt(input, value))
        {
            choice = value;

            switch (choice)
            {
            case 1:
                createAccount(bank);
                break;
            case 2:
                closeAccount(bank);
                break;
            case 3:
                createUser(bank);
                break;
            case 4:
                deleteUser(bank);
                break;
            case 5:
                displayAllAccounts(bank);
                break;
            case 6:
                std::cout << "Logging out\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
            }
        }
        else
        {
            std::cout << "Please enter the correct number\n";
        }
    } while (choice != 6);
}

void Admin::createUser(IBank &bank)
{
    bank.addUser();
}

void Admin::deleteUser(IBank &bank)
{
    bank.removeUser();
}

void Admin::displayAllAccounts(IBank &bank)
{
    bank.showAllAccounts();
}
