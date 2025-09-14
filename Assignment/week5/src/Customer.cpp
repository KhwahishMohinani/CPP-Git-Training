#include <iostream>
#include "../include/Customer.h"
#include "../include/IAccount.h"
#include "../include/IBank.h"
#include "../include/InputHandler.h"

Customer::Customer(std::string name, int contact, int userId, std::string password, std::string type)
{
    this->name = name;
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
        if (amount > account->getBalance())
        {
            std::cout << "Insufficient balance\n";
        }
        else
        {
            account->subtractBalance(amount);
            std::cout << "Withdrawn " << amount << " successfully. New balance: " << account->getBalance() << "\n";
        }
    }
    else
    {
        std::cout << "You don't own this account\n";
    }
}

void Customer::showMenu(IBank &bank)
{
    InputHandler inputHandler;
    int choice, value;
    std::string input;
    do
    {
        std::cout << "1. Create new Account\n2. Access Existing Account\n3. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> input;
        if (inputHandler.isValidInt(input, value))
        {
            choice = value;
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
                long accountNumber, longValue;
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
                        while (true)
                        {
                            std::cin >> input;
                            if (inputHandler.isValidInt(input, value))
                            {
                                accountMenuChoice = value;
                                break;
                            }
                            else
                            {
                                std::cout << "Please enter the correct number\n";
                            }
                        }
                        switch (accountMenuChoice)
                        {
                        case 1:
                        {
                            double amount, doubleValue;
                            std::cout << "Enter the amount to deposit: ";
                            while (true)
                            {
                                if (inputHandler.isValidDouble(doubleValue))
                                {
                                    amount = doubleValue;
                                    break;
                                }
                                else
                                {
                                    std::cout << "Please enter valid amount\n";
                                }
                            }
                            deposit(account, amount);
                            break;
                        }
                        case 2:
                        {
                            double amount, doubleValue;
                            std::cout << "Enter the amount to withdraw: ";
                            while (true)
                            {
                                if (inputHandler.isValidDouble(doubleValue))
                                {
                                    amount = doubleValue;
                                    break;
                                }
                                else
                                {
                                    std::cout << "Please enter valid amount\n";
                                }
                            }
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
        }
        else
        {
            std::cout << "Please enter the correct number\n";
        }
    } while (choice != 3);
}
