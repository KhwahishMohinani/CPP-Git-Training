#ifndef MENU_H
#define MENU_H

#include <string>
class IBank;
class Customer;
class Admin;
class IAccount;
class InputHandler;

int getValidInt(const std::string &prompt, InputHandler &inputHandler);
long getValidLong(const std::string &prompt, InputHandler &inputHandler);
double getValidDouble(const std::string &prompt, InputHandler &inputHandler);
Customer *handleCustomerLogin(IBank &bank, InputHandler &inputHandler);
Admin *handleAdminLogin(IBank &bank, InputHandler &inputHandler);
void loginMenu(IBank &bank, InputHandler &inputHandler);
void depositMenu(IAccount *account, Customer &customer, InputHandler &inputHandler);
void withdrawMenu(IAccount *account, Customer &customer, InputHandler &inputHandler);
void showTransactions(int start, IAccount *account);
void showMiniStatement(IAccount *account);
void showBankStatement(IAccount *account);
void handleAccountMenu(IAccount *account, Customer &customer, InputHandler &inputHandler);
void showCustomerMenu(IBank &bank, Customer &customer, InputHandler &inputHandler);
void menuForAddAccount(IBank &bank, InputHandler &inputHandler, int customerId);
void menuForAddAccount(Admin &admin, InputHandler &inputHandler, int customerId);
void readUserInput(std::string &password, std::string &name);
void printCustomerCreated(Customer *customer);
void menuForAddCustomer(IBank &bank);
void menuForAddCustomer(Admin &admin);
void menuForRemoveAccount(Admin &admin, InputHandler &inputHandler);
void showAllAccounts(Admin &admin);
void showAllCustomers(Admin &admin);
void menuForRemoveCustomer(Admin &admin, InputHandler &inputHandler);
void showAdminMenu(IBank &bank, Admin &admin, InputHandler &inputHandler);

#endif
