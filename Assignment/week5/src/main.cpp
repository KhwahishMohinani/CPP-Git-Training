#include <iostream>
#include "IBank.h"
#include "Bank.h"
#include "IAccount.h"
#include "User.h"
#include "Admin.h"
#include "Customer.h"
#include "InputHandler.h"
#include "menu.h"

int main()
{
    User user;
    IBank *iBankPtr = new Bank();
    InputHandler inputHandler;
    int choice, value;
    std::string input, type;
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
                user.signUp(*iBankPtr);
                break;
            }
            case 2:
            {
                User *loggedInUser = user.login(*iBankPtr);
                if (loggedInUser)
                {
                    std::cout << "Login successful!\n";
                    type = loggedInUser->getType();
                    if (type == "customer")
                    {
                        Customer *customer = dynamic_cast<Customer *>(loggedInUser);
                        if (customer)
                        {
                            showCustomerMenu(*iBankPtr, *customer);
                        }
                    }
                    else
                    {
                        Admin *admin = dynamic_cast<Admin *>(loggedInUser);
                        if (admin)
                        {
                            showAdminMenu(*iBankPtr, *admin);
                        }
                    }
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
