#ifndef MENU_H
#define MENU_H

#include <string>
class IBank;
class Customer;
class Admin;
class IAccount;
class InputHandler;
class Transaction;

int getValidInt(const std::string &prompt, InputHandler &inputHandler);
long getValidLong(const std::string &prompt, InputHandler &inputHandler);
double getValidDouble(const std::string &prompt, InputHandler &inputHandler);
void inputCredentials(int &id, std::string &password, InputHandler &inputHandler);
void loginMenu(IBank &bank, InputHandler &inputHandler);
void depositMenu(IBank &bank, long accountNumber, Customer &customer);
void withdrawMenu(IBank &bank, long accountNumber, Customer &customer);
void showTransactions(int start, Transaction **transactions, int transactionsCount);
void showMiniStatement(IBank &bank, long accountNumber, Customer &customer);
void showBankStatement(IBank &bank, long accountNumber, Customer &customer);
void handleAccountMenu(IBank &bank, int accountNumber, Customer &customer);
void showCustomerMenu(IBank &bank, Customer &customer, InputHandler &inputHandler);
void AccountCreationRequestMenu(IBank &bank, Customer &customer, InputHandler &inputHandler);
void menuForAddAccount(Admin &admin, InputHandler &inputHandler, int customerId);
void readUserDetailsInput(std::string &password, std::string &name);
void printCustomerCreated(Customer *customer);
void signupMenu(IBank &bank);
void menuForRemoveAccount(Admin &admin, InputHandler &inputHandler);
void showAllAccounts(Admin &admin);
void showAllCustomers(Admin &admin);
void showAdminMenu(IBank &bank, Admin &admin, InputHandler &inputHandler);
void showCustomerAccounts(IBank &bank, Customer &customer, InputHandler inputHandler);

#endif
