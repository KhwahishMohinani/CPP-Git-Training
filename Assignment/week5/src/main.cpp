#include <iostream>
#include "../include/IBank.h"
#include "../include/Bank.h"
#include "../include/IAccount.h"
#include "../include/User.h"
#include "../include/InputHandler.h"

int main()
{
    User user;
    IBank *iBankPtr = new Bank();
    InputHandler inputHandler;
    int choice, value;
    std::string input;
    do
    {
        std::cout << "1. Signup\n2. Login\n3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> input;
        if (inputHandler.isValidInt(input, value))
        {
            choice = value;
            switch (choice)
            {
            case 1:
            {
                iBankPtr->addUser();
                break;
            }
            case 2:
            {
                User *loggedInUser = user.login(*iBankPtr);
                if (loggedInUser)
                {
                    std::cout << "Login successful!\n";
                    loggedInUser->showMenu(*iBankPtr);
                }
                else
                {
                    std::cout << "Login failed!\n";
                }
                break;
            }
            case 3:
            {
                std::cout << "Exiting\n";
                break;
            }
            default:
            {
                std::cout << "Invalid choice\n";
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
