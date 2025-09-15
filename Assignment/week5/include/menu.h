#ifndef MENU_H
#define MENU_H

class IBank;
class Customer;
class Admin;

void showCustomerMenu(IBank &bank, Customer &customer);
void showAdminMenu(IBank &bank, Admin &admin);

#endif
