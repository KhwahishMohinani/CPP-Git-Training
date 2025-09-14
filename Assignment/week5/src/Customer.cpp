#include <iostream>
#include "../include/Customer.h"
#include "../include/IAccount.h"
#include "../include/IBank.h"

Customer::Customer(std::string name, std::string email, int contact, int userId, std::string password, std::string type)
{
    this->name = name;
    this->email = email;
    this->contact = contact;
    setUserId(userId);
    setPassword(password);
    setType(type);
}

void Customer::deposit(IAccount *account, double amount)
{
    if (account && account->getCustomerId() == this->getUserId())
    {
        account->addBalance(amount);
        std::cout << "Deposited " << amount << " successfully. New balance: " << account->getBalance() << "\n";
    }
    else
    {
        std::cout << "You don't own this account\n";
    }
}

void Customer::withdraw(IAccount *account, double amount)
{
    if (account && account->getCustomerId() == this->getUserId())
    {
        account->subtractBalance(amount);
        std::cout << "Withdrawn " << amount << " successfully. New balance: " << account->getBalance() << "\n";
    }
    else
    {
        std::cout << "You don't own this account\n";
    }
}

void Customer::showMenu(IBank &bank)
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
        {
            bank.addAccount(this);
            break;
        }
        case 2:
        {
            std::cout << "Enter Account number: ";
            long accountNumber;
            std::cin >> accountNumber;
            IAccount *account = bank.getAccount(accountNumber, getUserId());
            if (!account)
                std::cout << "Account not found or does not belong to you!\n";
            else
            {
                int accountMenuChoice;
                do
                {
                    std::cout << "1. Deposit money\n2. Withdraw money\n3. Display mini statement\n4. Display bank statement\n5. Back\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> accountMenuChoice;
                    switch (accountMenuChoice)
                    {
                    case 1:
                    {
                        double amount;
                        std::cout << "Enter the amount to deposit: ";
                        std::cin >> amount;
                        deposit(account, amount);
                        break;
                    }
                    case 2:
                    {
                        double amount;
                        std::cout << "Enter the amount to withdraw: ";
                        std::cin >> amount;
                        withdraw(account, amount);
                        break;
                    }
                    case 3:
                        account->showMiniStatement();
                        break;
                    case 4:
                        account->showBankStatement();
                        break;
                    case 5:
                        std::cout << "Returning to customer menu\n";
                        break;
                    default:
                        std::cout << "Invalid choice!\n";
                    }
                } while (accountMenuChoice != 5);

                break;
            }
        }
        case 3:
        {
            std::cout << "Logging out\n";
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Try again\n";
            break;
        }
        }
    } while (choice != 3);
}
