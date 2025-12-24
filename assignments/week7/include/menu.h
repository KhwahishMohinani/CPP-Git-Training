#ifndef MENU_H
#define MENU_H

#include <string>
class IBank;
class Customer;
class Admin;
class IAccount;
class InputHandler;
class Transaction;

int getValidInt(const std::string &prompt);
long getValidLong(const std::string &prompt);
double getValidDouble(const std::string &prompt);
void inputCredentials(int &id, std::string &password);
void loginMenu(IBank &bank);
void depositMenu(IBank &bank, long accountNumber, Customer &customer);
void withdrawMenu(IBank &bank, long accountNumber, Customer &customer);
void showTransactions(int start, Transaction **transactions, int transactionsCount);
void showMiniStatement(IBank &bank, long accountNumber, Customer &customer);
void showBankStatement(IBank &bank, long accountNumber, Customer &customer);
void handleAccountMenu(IBank &bank, int accountNumber, Customer &customer);
void showCustomerMenu(IBank &bank, Customer &customer);
void AccountCreationRequestMenu(IBank &bank, Customer &customer);
void menuForAddAccount(Admin &admin, int customerId);
void readUserDetailsForSignup(std::string &password, std::string &name);
void printCustomerCreated(Customer *customer);
void signupMenu(IBank &bank);
void menuForRemoveAccount(Admin &admin);
void showAllAccounts(Admin &admin);
void showAllCustomers(Admin &admin);
void showAdminMenu(IBank &bank, Admin &admin);
void showCustomerAccounts(IBank &bank, Customer &customer);

#endif
