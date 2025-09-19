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

void inputCredentials(int &id, std::string &password, InputHandler &inputHandler)
{
    id = getValidInt("Enter user id: ", inputHandler);
    std::cout << "Enter password: ";
    std::cin >> password;
}

void loginMenu(IBank &bank, InputHandler &inputHandler)
{
    int id;
    std::string password;
    inputCredentials(id, password, inputHandler);
    Customer *customer = bank.findCustomerByCredentials(id, password);
    Admin *admin = bank.findAdminByCredentials(id, password);
    if (customer)
    {
        std::cout << "Login successful\n";
        showCustomerMenu(bank, *customer, inputHandler);
    }
    else if (admin)
    {
        std::cout << "Login successful\n";
        showAdminMenu(bank, *admin, inputHandler);
    }
    else
    {
        std::cout << "Invalid credentials.\n";
    }
}

void depositMenu(IBank &bank, long accountNumber, Customer &customer)
{
    InputHandler inputHandler;
    double amount = getValidDouble("Enter amount to deposit: ", inputHandler);
    if (bank.deposit(accountNumber, customer.getUserId(), amount))
    {
        std::cout << "Deposited " << amount << " succesfully" << "\n";
    }
    else
    {
        std::cout << "You don't own this account\n";
    }
}

void withdrawMenu(IBank &bank, long accountNumber, Customer &customer)
{
    InputHandler inputHandler;
    double amount = getValidDouble("Enter amount to withdraw: ", inputHandler);

    if (bank.withdraw(accountNumber, customer.getUserId(), amount))
    {
        std::cout << "Withdrawn " << amount << " successfully\n";
    }
    else
    {
        std::cout << "Insufficient balance\n";
    }
}

void showCustomerAccounts(IBank &bank, Customer &customer, InputHandler inputHandler)
{
    int accountCount = 0;
    IAccount **accounts = bank.getAccountsByCustomerId(customer.getUserId(), accountCount);

    if (accountCount == 0)
    {
        std::cout << "No accounts found for Customer ID: " << customer.getUserId() << "\n";
    }
    else
    {
        for (int i = 0; i < accountCount; i++)
        {
            std::cout << "Account No: " << accounts[i]->getAccountNumber()
                      << " | Balance: " << accounts[i]->getBalance()
                      << " | Type: " << accounts[i]->getAccountType() << "\n";
        }
        delete[] accounts;
    }
}

void showTransactions(int start, Transaction **transactions, int transactionsCount)
{
    for (int i = start; i < transactionsCount; i++)
    {
        std::cout << "Transaction Id: " << transactions[i]->getTransactionId();
        std::cout << " | Account Number: " << transactions[i]->getAccountNumber();
        std::cout << " | Transaction type: " << transactions[i]->getType();
        std::cout << " | Amount: " << transactions[i]->getAmount() << "\n";
    }
}

void showMiniStatement(IBank &bank, long accountNumber, Customer &customer)
{
    int start = 0;
    int transactionsCount = bank.getAccountTransactionsCount(accountNumber, customer.getUserId());
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
        showTransactions(start, bank.getAccountTransactions(accountNumber, customer.getUserId()), transactionsCount);
    }
}

void showBalance(IBank &bank, long accountNumber, Customer &customer)
{
    std::cout << "Balance: " << bank.getAccountBalance(accountNumber, customer.getUserId()) << "\n";
}

void showBankStatement(IBank &bank, long accountNumber, Customer &customer)
{
    int transactionsCount = bank.getAccountTransactionsCount(accountNumber, customer.getUserId());
    if (transactionsCount == 0)
    {
        std::cout << "No transactions yet\n";
    }
    else
    {
        std::cout << "Bank Statement:\n";
        showTransactions(0, bank.getAccountTransactions(accountNumber, customer.getUserId()), transactionsCount);
    }
}

void handleAccountMenu(IBank &bank, int accountNumber, Customer &customer)
{
    InputHandler inputHandler;
    int choice;
    do
    {
        choice = getValidInt("1. Deposit money\n2. Withdraw money\n3. Mini statement\n4. Bank statement\n5. Show Balance \n6. Back\nEnter choice: ", inputHandler);
        switch (choice)
        {
        case 1:
            depositMenu(bank, accountNumber, customer);
            break;
        case 2:
            withdrawMenu(bank, accountNumber, customer);
            break;
        case 3:
            showMiniStatement(bank, accountNumber, customer);
            break;
        case 4:
            showBankStatement(bank, accountNumber, customer);
            break;
        case 5:
            showBalance(bank, accountNumber, customer);
            break;
        case 6:
            std::cout << "Returning...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    } while (choice != 6);
}

void showCustomerMenu(IBank &bank, Customer &customer, InputHandler &inputHandler)
{
    int choice;
    do
    {
        choice = getValidInt("1. Create Account\n2. Access Account\n3. Show my accounts\n4. Logout\nEnter choice: ", inputHandler);
        switch (choice)
        {
        case 1:
            AccountCreationRequestMenu(bank, customer, inputHandler);
            break;
        case 2:
        {
            long accountNumber = getValidLong("Enter Account number: ", inputHandler);
            if (bank.getAccount(accountNumber, customer.getUserId()))
                handleAccountMenu(bank, accountNumber, customer);
            else
                std::cout << "Account not found.\n";
            break;
        }
        case 3:
        {
            showCustomerAccounts(bank, customer, inputHandler);
            break;
        }
        case 4:
        {
            std::cout << "Logging out...\n";
            break;
        }
        default:
        {
            std::cout << "Invalid choice!\n";
        }
        }
    } while (choice != 4);
}

void AccountCreationRequestMenu(IBank &bank, Customer &customer, InputHandler &inputHandler)
{
    std::string type;
    std::cout << "Enter the account type (current/savings): ";
    std::cin >> type;
    double balance = getValidDouble("Enter initial balance: ", inputHandler);
    if (bank.addAccountRequest(customer.getUserId(), balance, type))
    {
        std::cout << "Request sent successfully!\n";
    }
    else
    {
        std::cout << "Request queue is full!\n";
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

    double balance = getValidDouble("Enter the inital balance: ", inputHandler);

    IAccount *newAccount = admin.createAccount(*customer, balance, accountType);
    if (newAccount)
    {
        std::cout << "Account created successfully!\n";
        std::cout << "Account Number for " << customerId << " is: " << newAccount->getAccountNumber() << "\n";
    }
    else
    {
        std::cout << "Failed to create account (max limit reached)\n";
    }
}

void readUserDetailsInput(std::string &password, std::string &name)
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

void signupMenu(IBank &bank)
{
    std::string password, name;
    readUserDetailsInput(password, name);
    Customer *newCustomer = bank.addCustomer(name, password);
    printCustomerCreated(newCustomer);
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
    if (admin.fetchAccountsCount() == 0)
    {
        std::cout << "No accounts yet\n";
    }
    else
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
}

void showAllCustomers(Admin &admin)
{
    if (admin.fetchCustomersCount() == 0)
    {
        std::cout << "No accounts yet";
    }
    else
    {
        Customer **customers = admin.fetchAllCustomers();
        for (int i = 0; i < admin.fetchCustomersCount(); i++)
        {
            if (customers[i]->getUserType() == "customer")
            {
                std::cout << "Customer id: " << customers[i]->getUserId();
                std::cout << " | Name: " << customers[i]->getName() << "\n";
            }
        }
    }
}

void handleAccountRequestMenu(IBank &bank, Admin &admin)
{
    int requestCount = bank.getRequestCount();
    if (requestCount == 0)
    {
        std::cout << "No pending account requests\n";
    }
    else
    {
        admin.handleRequests();
        std::cout << "Accepted all requests. Accounts created\n";
    }
}

void showAdminMenu(IBank &bank, Admin &admin, InputHandler &inputHandler)
{
    int choice;
    do
    {
        choice = getValidInt("1. Create Account\n2. Close Account\n3. Show All Customers\n4. Show all accounts\n5. Process account requests\n6. Logout\nEnter choice: ", inputHandler);
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
            showAllCustomers(admin);
            break;
        case 4:
            showAllAccounts(admin);
            break;
        case 5:
            handleAccountRequestMenu(bank, admin);
            break;
        case 6:
            std::cout << "Logging out...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}
