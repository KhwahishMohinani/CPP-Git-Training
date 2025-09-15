#include <iostream>
#include "menu.h"
#include "IBank.h"
#include "Customer.h"
#include "Admin.h"
#include "InputHandler.h"

void showCustomerMenu(IBank &bank, Customer &customer)
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
                bank.addAccount(customer);
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
                IAccount *account = bank.getAccount(accountNumber, customer.getUserId());
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
                            customer.deposit(account, amount);
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
                            customer.withdraw(account, amount);
                            break;
                        }
                        case 3:
                            customer.showMiniStatement(account);
                            break;
                        case 4:
                            customer.showBankStatement(account);
                            break;
                        case 5:
                            std::cout << "Returning to customer menu\n";
                            break;
                        default:
                            std::cout << "Invalid choice!\n";
                        }
                    } while (accountMenuChoice != 5);
                }
                break;
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

void showAdminMenu(IBank &bank, Admin &admin)
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
                admin.createAccount(bank);
                break;
            case 2:
                admin.closeAccount(bank);
                break;
            case 3:
                admin.createUser(bank);
                break;
            case 4:
                admin.deleteUser(bank);
                break;
            case 5:
                admin.displayAllAccounts(bank);
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
