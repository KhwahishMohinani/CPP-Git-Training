#include <iostream>
#include "menu.h"
#include "IBank.h"
#include "Customer.h"
#include "Admin.h"
#include "IAccount.h"
#include "Transaction.h"
#include "InputHandler.h"
#include "constants.h"

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
        std::cout << INVALID_INPUT;
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
        std::cout << INVALID_LONG;
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
        std::cout << INVALID_DOUBLE;
    }
}

void inputCredentials(int &id, std::string &password, InputHandler &inputHandler)
{
    id = getValidInt(ENTER_USER_ID, inputHandler);
    std::cout << ENTER_PASSWORD;
    std::cin >> password;
}

void loginMenu(IBank &bank, InputHandler &inputHandler)
{
    int id;
    std::string password;
    inputCredentials(id, password, inputHandler);
    Customer *customer = bank.getCustomerByCredentials(id, password);
    Admin *admin = bank.getAdminByCredentials(id, password);
    if (customer)
    {
        std::cout << LOGIN_SUCCESS;
        showCustomerMenu(bank, *customer, inputHandler);
    }
    else if (admin)
    {
        std::cout << LOGIN_SUCCESS;
        showAdminMenu(bank, *admin, inputHandler);
    }
    else
    {
        std::cout << LOGIN_FAILED;
    }
}

void depositMenu(IBank &bank, long accountNumber, Customer &customer)
{
    InputHandler inputHandler;
    double amount = getValidDouble(ENTER_AMOUNT_DEPOSIT, inputHandler);
    if (bank.deposit(accountNumber, customer.getUserId(), amount))
    {
        std::cout << DEPOSIT_SUCCESS << amount << SUCCESS;
    }
    else
    {
        std::cout << DEPOSIT_FAILED;
    }
}

void withdrawMenu(IBank &bank, long accountNumber, Customer &customer)
{
    InputHandler inputHandler;
    double amount = getValidDouble(ENTER_AMOUNT_WITHDRAW, inputHandler);

    if (bank.withdraw(accountNumber, customer.getUserId(), amount))
    {
        std::cout << WITHDRAW_SUCCESS << amount << SUCCESS;
    }
    else
    {
        std::cout << WITHDRAW_FAILED;
    }
}

void showCustomerAccounts(IBank &bank, Customer &customer, InputHandler inputHandler)
{
    int accountCount = 0;
    IAccount **accounts = bank.getAccountsByCustomerId(customer.getUserId(), accountCount);

    if (accountCount == 0)
    {
        std::cout << NO_ACCOUNTS_FOUND << customer.getUserId() << "\n";
    }
    else
    {
        for (int i = 0; i < accountCount; i++)
        {
            std::cout << ACCOUNT_NUMBER_LABEL << accounts[i]->getAccountNumber()
                      << BALANCE_LABEL << accounts[i]->getBalance()
                      << ACCOUNT_TYPE_LABEL << accounts[i]->getAccountType() << "\n";
        }
        delete[] accounts;
    }
}

void showTransactions(int start, Transaction **transactions, int transactionsCount)
{
    for (int i = start; i < transactionsCount; i++)
    {
        std::cout << TRANSACTION_ID_LABEL << transactions[i]->getTransactionId();
        std::cout << TRANSACTION_ACCOUNT_NUMBER_LABEL << transactions[i]->getAccountNumber();
        std::cout << TRANSACTION_TYPE_LABEL << transactions[i]->getType();
        std::cout << TRANSACTION_AMOUNT_LABEL << transactions[i]->getAmount() << "\n";
    }
}

void showMiniStatement(IBank &bank, long accountNumber, Customer &customer)
{
    int start = 0;
    int transactionsCount = bank.getAccountTransactionsCount(accountNumber, customer.getUserId());
    if (transactionsCount == 0)
    {
        std::cout << NO_TRANSACTIONS;
    }
    else
    {
        if (transactionsCount > 5)
        {
            start = transactionsCount - 5;
        }
        std::cout << MINI_STATEMENT;
        showTransactions(start, bank.getAccountTransactions(accountNumber, customer.getUserId()), transactionsCount);
    }
}

void showBalance(IBank &bank, long accountNumber, Customer &customer)
{
    std::cout << BALANCE << bank.getAccountBalance(accountNumber, customer.getUserId()) << "\n";
}

void showBankStatement(IBank &bank, long accountNumber, Customer &customer)
{
    int transactionsCount = bank.getAccountTransactionsCount(accountNumber, customer.getUserId());
    if (transactionsCount == 0)
    {
        std::cout << NO_TRANSACTIONS;
    }
    else
    {
        std::cout << BANK_STATEMENT;
        showTransactions(0, bank.getAccountTransactions(accountNumber, customer.getUserId()), transactionsCount);
    }
}

void handleAccountMenu(IBank &bank, int accountNumber, Customer &customer)
{
    InputHandler inputHandler;
    int choice;
    do
    {
        choice = getValidInt(ACCOUNT_MENU, inputHandler);
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
            std::cout << RETURNING;
            break;
        default:
            std::cout << INVALID_CHOICE;
            break;
        }
    } while (choice != 6);
}

void showCustomerMenu(IBank &bank, Customer &customer, InputHandler &inputHandler)
{
    int choice;
    do
    {
        choice = getValidInt(CUSTOMER_MENU, inputHandler);
        switch (choice)
        {
        case 1:
            AccountCreationRequestMenu(bank, customer, inputHandler);
            break;
        case 2:
        {
            long accountNumber = getValidLong(ENTER_ACCOUNT_NUMBER, inputHandler);
            if (bank.getAccount(accountNumber, customer.getUserId()))
                handleAccountMenu(bank, accountNumber, customer);
            else
                std::cout << ACCOUNT_NOT_FOUND;
            break;
        }
        case 3:
        {
            showCustomerAccounts(bank, customer, inputHandler);
            break;
        }
        case 4:
        {
            std::cout << LOGGING_OUT;
            break;
        }
        default:
        {
            std::cout << INVALID_CHOICE;
        }
        }
    } while (choice != 4);
}

void AccountCreationRequestMenu(IBank &bank, Customer &customer, InputHandler &inputHandler)
{
    std::string type;
    std::cout << ENTER_ACCOUNT_TYPE;
    std::cin >> type;
    double balance = getValidDouble(ENTER_INITIAL_BALANCE, inputHandler);
    if (bank.addAccountRequest(customer.getUserId(), balance, type))
    {
        std::cout << REQUEST_SENT;
    }
    else
    {
        std::cout << REQUEST_FAILED;
    }
}

void menuForAddAccount(Admin &admin, InputHandler &inputHandler, int customerId)
{
    Customer *customer = admin.searchCustomerById(customerId);
    if (!customer)
    {
        std::cout << CUSTOMER_NOT_FOUND;
        return;
    }

    std::cout << ENTER_ACCOUNT_TYPE;
    std::string accountType;
    std::cin >> accountType;

    double balance = getValidDouble(ENTER_INITIAL_BALANCE, inputHandler);

    int accountId = admin.createAccount(*customer, balance, accountType);
    if (accountId != -1)
    {
        std::cout << ACCOUNT_CREATED;
        std::cout << ACCOUNT_NUMBER_FOR_LABEL << customerId << IS_LABEL << accountId << "\n";
    }
    else
    {
        std::cout << ACCOUNT_FAILED;
    }
}

void readUserDetailsInput(std::string &password, std::string &name)
{
    std::cout << ENTER_PASSWORD;
    std::cin >> password;

    std::cout << ENTER_NAME;
    std::cin >> name;
}

void printCustomerCreated(Customer *customer)
{
    std::cout << CUSTOMER_CREATED;
    std::cout << YOUR_CUSTOMER_ID << customer->getUserId() << "\n";
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
    int customerId = getValidInt(ENTER_CUSTOMER_ID, inputHandler);
    Customer *customer = admin.searchCustomerById(customerId);
    if (!customer)
    {
        std::cout << CUSTOMER_NOT_FOUND;
        return;
    }

    long accountNumber = getValidLong(ENTER_ACCOUNT_NUMBER, inputHandler);

    if (!admin.deleteAccount(accountNumber, customerId))
    {
        std::cout << ACCOUNT_NOT_FOUND;
    }
    else
    {
        std::cout << ACCOUNT_REMOVED;
    }
}

void menuForRemoveCustomer(IBank &bank, Admin &admin, InputHandler &inputHandler)
{
    int id = getValidInt(ENTER_CUSTOMER_ID_REMOVE, inputHandler);

    int beforeCount = bank.getCustomersCount();
    admin.deleteCustomer(id);
    int afterCount = bank.getCustomersCount();

    if (beforeCount == afterCount)
    {
        std::cout << CUSTOMER_WITH_ID_PREFIX << id << CUSTOMER_WITH_ID_NOT_FOUND_SUFFIX;
    }
    else
    {
        std::cout << CUSTOMER_WITH_ID_PREFIX << id << CUSTOMER_WITH_ID_REMOVED_SUFFIX;
    }
}

void showAllAccounts(Admin &admin)
{
    if (admin.fetchAccountsCount() == 0)
    {
        std::cout << NO_ACCOUNTS;
    }
    else
    {
        IAccount **accounts = admin.fetchAllAccounts();
        for (int i = 0; i < admin.fetchAccountsCount(); i++)
        {
            std::cout << ACCOUNT_NUMBER_LABEL << accounts[i]->getAccountNumber();
            std::cout << BALANCE_LABEL << accounts[i]->getBalance();
            std::cout << ACCOUNT_OWNER_ID_LABEL << accounts[i]->getCustomerId();
            std::cout << ACCOUNT_TYPE_LABEL << accounts[i]->getAccountType() << "\n";
        }
    }
}

void showAllCustomers(Admin &admin)
{
    if (admin.fetchCustomersCount() == 0)
    {
        std::cout << NO_CUSTOMERS;
    }
    else
    {
        Customer **customers = admin.fetchAllCustomers();
        for (int i = 0; i < admin.fetchCustomersCount(); i++)
        {
            if (customers[i]->getUserType() == CUSTOMER)
            {
                std::cout << CUSTOMER_ID_LABEL << customers[i]->getUserId();
                std::cout << NAME_LABEL << customers[i]->getName() << "\n";
            }
        }
    }
}

void handleAccountRequestMenu(IBank &bank, Admin &admin)
{
    int requestCount = bank.getRequestCount();
    if (requestCount == 0)
    {
        std::cout << NO_REQUESTS;
    }
    else
    {
        int createdCount = admin.handleRequests();
        if (createdCount > 0)
        {
            std::cout << REQUESTS_PROCESSED << requestCount
                      << CREATED_ACCOUNT << createdCount << ".\n";
        }
        else
        {
            std::cout << REQUESTS_FAILED;
        }
    }
}

void showAdminMenu(IBank &bank, Admin &admin, InputHandler &inputHandler)
{
    int choice;
    do
    {
        choice = getValidInt(ADMIN_MENU, inputHandler);
        switch (choice)
        {
        case 1:
        {
            int customerId = getValidInt(ENTER_CUSTOMER_ID, inputHandler);
            menuForAddAccount(admin, inputHandler, customerId);
            break;
        }
        case 2:
        {
            menuForRemoveAccount(admin, inputHandler);
            break;
        }
        case 3:
        {
            showAllCustomers(admin);
            break;
        }
        case 4:
        {
            showAllAccounts(admin);
            break;
        }
        case 5:
        {
            menuForRemoveCustomer(bank, admin, inputHandler);
            break;
        }
        case 6:
        {
            handleAccountRequestMenu(bank, admin);
            break;
        }
        case 7:
        {
            std::cout << LOGGING_OUT;
            break;
        }
        default:
        {
            std::cout << INVALID_CHOICE;
        }
        }
    } while (choice != 7);
}
