#include <iostream>
#include "IBank.h"
#include "Bank.h"
#include "InputHandler.h"
#include "menu.h"
#include "constants.h"

int main()
{
    IBank *bank = new Bank(1, "MyBank", "Admin4", "admin123");
    InputHandler inputHandler;
    int choice;
    do
    {
        choice = getValidInt(USER_MENU, inputHandler);
        switch (choice)
        {
        case 1:
        {
            signupMenu(*bank);
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
