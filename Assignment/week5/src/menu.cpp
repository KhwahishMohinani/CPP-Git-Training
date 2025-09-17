#include <iostream>
#include "menu.h"
#include "IBank.h"
#include "Customer.h"
#include "Admin.h"
#include "IAccount.h"
#include "Transaction.h"
#include "InputHandler.h"

int getValidInt(const std::string &prompt, InputHandler &inputHandler)
{
    std::string input;
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> input;
        if (inputHandler.isValidInt(input, value))
        {
            return value;
        }
        std::cout << "Invalid input. Please enter a number.\n";
    }
}

long getValidLong(const std::string &prompt, InputHandler &inputHandler)
{
    std::string input;
    long value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> input;
        if (inputHandler.isValidLong(input, value))
        {
            return value;
        }
        std::cout << "Invalid input. Please enter a valid number.\n";
    }
}

double getValidDouble(const std::string &prompt, InputHandler &inputHandler)
{
    double value;
    while (true)
    {
        std::cout << prompt;
        if (inputHandler.isValidDouble(value))
        {
            return value;
        }
        std::cout << "Invalid input. Please enter a valid amount.\n";
    }
}

Customer *handleCustomerLogin(IBank &bank, InputHandler &inputHandler)
{
    int id = getValidInt("Enter customer id: ", inputHandler);
    std::string password;
    std::cout << "Enter password: ";
    std::cin >> password;

    return bank.findCustomerByCredentials(id, password);
}

Admin *handleAdminLogin(IBank &bank, InputHandler &inputHandler)
{
    int id = getValidInt("Enter admin id: ", inputHandler);
    std::string password;
    std::cout << "Enter password: ";
    std::cin >> password;

    return bank.findAdminByCredentials(id, password);
}

void loginMenu(IBank &bank, InputHandler &inputHandler)
{
    int choice = getValidInt("Login as:\n1. Customer\n2. Admin\nEnter choice: ", inputHandler);

    switch (choice)
    {
    case 1:
    {
        Customer *customer = handleCustomerLogin(bank, inputHandler);
        if (customer)
        {
            std::cout << "Login successful\n";
            showCustomerMenu(bank, *customer, inputHandler);
        }
        else
            std::cout << "Invalid credentials.\n";
        break;
    }
    case 2:
    {
        Admin *admin = handleAdminLogin(bank, inputHandler);
        if (admin)
        {
            std::cout << "Login successful\n";
            showAdminMenu(bank, *admin, inputHandler);
        }
        else
            std::cout << "Invalid credentials.\n";
        break;
    }
    default:
        std::cout << "Invalid choice!\n";
    }
}

void depositMenu(IAccount *account, Customer &customer, InputHandler &inputHandler)
{
    double amount = getValidDouble("Enter amount to deposit: ", inputHandler);
    if (account && account->getCustomerId() == customer.getUserId())
    {
        account->addBalance(amount);
        std::cout << "Deposited " << amount << " succesfully. New Balance is " << account->getBalance() << "\n";
    }
    else
    {
        std::cout << "You don't own this account\n";
    }
}

void withdrawMenu(IAccount *account, Customer &customer, InputHandler &inputHandler)
{
    double amount = getValidDouble("Enter amount to withdraw: ", inputHandler);
    if (account && account->getCustomerId() == customer.getUserId())
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

void showTransactions(int start, IAccount *account)
{
    Transaction **transactions = account->getTransactions();
    for (int i = start; i < account->getTransactionsCount(); i++)
    {
        std::cout << "Transaction Id: " << transactions[i]->getTransactionId();
        std::cout << " | Account Number: " << transactions[i]->getAccountNumber();
        std::cout << " | Transaction type: " << transactions[i]->getType();
        std::cout << " | Amount: " << transactions[i]->getAmount() << "\n";
    }
}

void showMiniStatement(IAccount *account)
{
    int start = 0;
    int transactionsCount = account->getTransactionsCount();
    if (transactionsCount == 0)
    {
        std::cout << "No transactions yet\n";
    }
    else
    {
        if (transactionsCount > 5)
        {
            start = transactionsCount - 5;
        }
        std::cout << "Mini Statement(Last 5 transactions):\n";
        showTransactions(start, account);
    }
}

void showBankStatement(IAccount *account)
{
    int transactionsCount = account->getTransactionsCount();
    if (transactionsCount == 0)
    {
        std::cout << "No transactions yet\n";
    }
    else
    {
        std::cout << "Bank Statement:\n";
        showTransactions(0, account);
    }
}

void handleAccountMenu(IAccount *account, Customer &customer, InputHandler &inputHandler)
{
    int choice;
    do
    {
        choice = getValidInt("1. Deposit money\n2. Withdraw money\n3. Mini statement\n4. Bank statement\n5. Back\nEnter choice: ", inputHandler);
        switch (choice)
        {
        case 1:
            depositMenu(account, customer, inputHandler);
            break;
        case 2:
            withdrawMenu(account, customer, inputHandler);
            break;
        case 3:
            showMiniStatement(account);
            break;
        case 4:
            showBankStatement(account);
            break;
        case 5:
            std::cout << "Returning...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

void showCustomerMenu(IBank &bank, Customer &customer, InputHandler &inputHandler)
{
    int choice;
    do
    {
        choice = getValidInt("1. Create Account\n2. Access Account\n3. Logout\nEnter choice: ", inputHandler);
        switch (choice)
        {
        case 1:
            menuForAddAccount(bank, inputHandler, customer.getUserId());
            break;
        case 2:
        {
            long accountNumber = getValidLong("Enter Account number: ", inputHandler);
            IAccount *account = bank.getAccount(accountNumber, customer.getUserId());
            if (account)
                handleAccountMenu(account, customer, inputHandler);
            else
                std::cout << "Account not found.\n";
            break;
        }
        case 3:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

void menuForAddAccount(IBank &bank, InputHandler &inputHandler, int customerId)
{
    Customer *customer = bank.findCustomerById(customerId);
    if (!customer)
    {
        std::cout << "Customer not found\n";
        return;
    }

    std::cout << "Enter the account type (current/savings): ";
    std::string accountType;
    std::cin >> accountType;

    IAccount *newAccount = bank.addAccount(*customer, accountType);
    if (newAccount)
    {
        std::cout << "Account created successfully!\n";
        std::cout << "Your Account Number is: " << newAccount->getAccountNumber() << "\n";
    }
    else
    {
        std::cout << "Failed to create account (max limit reached)\n";
    }
}

void menuForAddAccount(Admin &admin, InputHandler &inputHandler, int customerId)
{
    Customer *customer = admin.searchCustomerById(customerId);
    if (!customer)
    {
        std::cout << "Customer not found\n";
        return;
    }

    std::cout << "Enter the account type (current/savings): ";
    std::string accountType;
    std::cin >> accountType;

    IAccount *newAccount = admin.createAccount(*customer, accountType);
    if (newAccount)
    {
        std::cout << "Account created successfully!\n";
        std::cout << "Your Account Number is: " << newAccount->getAccountNumber() << "\n";
    }
    else
    {
        std::cout << "Failed to create account (max limit reached)\n";
    }
}

void readUserInput(std::string &password, std::string &name)
{
    std::cout << "Enter Password: ";
    std::cin >> password;

    std::cout << "Enter Name: ";
    std::cin >> name;
}

void printCustomerCreated(Customer *customer)
{
    std::cout << "Customer created successfully!\n";
    std::cout << "Your Customer ID is: " << customer->getUserId() << "\n";
}

void menuForAddCustomer(IBank &bank)
{
    std::string password, name;
    readUserInput(password, name);
    Customer *newCustomer = bank.addCustomer(name, password);
    printCustomerCreated(newCustomer);
}

void menuForAddCustomer(Admin &admin)
{
    std::string password, name;
    readUserInput(password, name);
    Customer *newCustomer = admin.createCustomer(name, password);
    printCustomerCreated(newCustomer);
}

void menuForRemoveCustomer(Admin &admin, InputHandler &inputHandler)
{
    int id = getValidInt("Enter customer id to remove: ", inputHandler);

    if (admin.searchCustomerById(id))
    {
        admin.deleteCustomerById(id);
        std::cout << "Customer removed successfully!\n";
    }
    else
    {
        std::cout << "User not found!\n";
    }
}

void menuForRemoveAccount(Admin &admin, InputHandler &inputHandler)
{
    int customerId = getValidInt("Enter Customer ID: ", inputHandler);
    Customer *customer = admin.searchCustomerById(customerId);
    if (!customer)
    {
        std::cout << "Customer not found.\n";
        return;
    }

    long accountNumber = getValidLong("Enter Account Number: ", inputHandler);

    IAccount *account = admin.fetchAccount(accountNumber, customerId);
    if (!account)
    {
        std::cout << "Account not found or does not belong to this customer.\n";
        return;
    }

    admin.deleteAccount(account);
    std::cout << "Account removed successfully!\n";
}

void showAllAccounts(Admin &admin)
{
    IAccount **accounts = admin.fetchAllAccounts();
    for (int i = 0; i < admin.fetchAccountsCount(); i++)
    {
        std::cout << "Account Number: " << accounts[i]->getAccountNumber();
        std::cout << " | Balance: " << accounts[i]->getBalance();
        std::cout << " | Customer Id: " << accounts[i]->getCustomerId();
        std::cout << " | Account Type: " << accounts[i]->getAccountType() << "\n";
    }
}

void showAllCustomers(Admin &admin)
{
    Customer **customers = admin.fetchAllCustomers();
    for (int i = 0; i < admin.fetchCustomersCount(); i++)
    {
        if (customers[i]->getType() == "customer")
        {
            std::cout << "Customer id: " << customers[i]->getUserId();
            std::cout << " | Name: " << customers[i]->getName() << "\n";
        }
    }
}

void showAdminMenu(IBank &bank, Admin &admin, InputHandler &inputHandler)
{
    int choice;
    do
    {
        choice = getValidInt("1. Create Account\n2. Close Account\n3. Create User\n4. Delete User\n5. Show All Customers\n6. Show all accounts\n7. Logout\nEnter choice: ", inputHandler);
        switch (choice)
        {
        case 1:
        {
            int customerId = getValidInt("Enter Customer ID: ", inputHandler);
            menuForAddAccount(admin, inputHandler, customerId);
            break;
        }
        case 2:
            menuForRemoveAccount(admin, inputHandler);
            break;
        case 3:
            menuForAddCustomer(admin);
            break;
        case 4:
            menuForRemoveCustomer(admin, inputHandler);
            break;
        case 5:
            showAllCustomers(admin);
            break;
        case 6:
            showAllAccounts(admin);
            break;
        case 7:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 7);
}
