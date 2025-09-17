#include <iostream>
#include "IBank.h"
#include "Bank.h"
#include "InputHandler.h"
#include "menu.h"

int main()
{
    IBank *bank = new Bank();
    InputHandler inputHandler;
    int choice;
    do
    {
        choice = getValidInt("1. Signup\n2. Login\n3. Exit\nEnter your choice: ", inputHandler);
        switch (choice)
        {
        case 1:
        {
            menuForAddCustomer(*bank);
            break;
        }
        case 2:
        {
            loginMenu(*bank, inputHandler);
            break;
        }
        case 3:
        {
            std::cout << "Exiting...\n";
            break;
        }
        default:
        {
            std::cout << "Invalid choice\n";
            break;
        }
        }
    } while (choice != 3);
}
