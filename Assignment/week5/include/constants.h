#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "structs.h"

const int MAX_TRANSACTIONS = 100;
const int MAX_CUSTOMERS = 100;
const int MAX_ADMINS = 100;
const int MAX_ACCOUNTS = 100;
const int MAX_REQUESTS = 100;
const int ACCOUNT_NOT_FOUND_CODE = 0;
const int WITHDRAW_SUCCESS_CODE = 1;
const int DEPOSIT_SUCCESS_CODE = 1;
const int TRANSACTION_LIMIT_EXCEEDED = 2;
const int INSUFFICIENT_BALANCE_CODE = 3;

const char ENTER_USER_ID[] = "Enter user id: ";
const char ENTER_PASSWORD[] = "Enter password: ";
const char ENTER_NAME[] = "Enter name: ";
const char ENTER_AMOUNT_DEPOSIT[] = "Enter amount to deposit: ";
const char ENTER_AMOUNT_WITHDRAW[] = "Enter amount to withdraw: ";
const char ENTER_ACCOUNT_TYPE[] = "Enter the account type\n1. Current\n2. Savings\nEnter your choice: ";
const char ENTER_INITIAL_BALANCE[] = "Enter the initial balance: ";
const char ENTER_CUSTOMER_ID[] = "Enter Customer ID: ";
const char ENTER_ACCOUNT_NUMBER[] = "Enter Account number: ";
const char ENTER_CUSTOMER_ID_REMOVE[] = "Enter Customer ID to remove: ";
const char INVALID_INPUT[] = "Invalid input. Please enter a number.\n";
const char INVALID_LONG[] = "Invalid input. Please enter a valid number.\n";
const char INVALID_DOUBLE[] = "Invalid input. Please enter a valid amount.\n";
const char INVALID_CHOICE[] = "Invalid choice\n";
const char LOGIN_SUCCESS[] = "Login successful\n";
const char LOGIN_FAILED[] = "Invalid credentials.\n";
const char DEPOSIT_SUCCESS[] = "Deposited ";
const char SUCCESS[] = " successfully\n";
const char DEPOSIT_FAILED[] = "Deposit Failed\n";
const char WITHDRAW_SUCCESS[] = "Withdrawn ";
const char INSUFFICIENT_BALANCE[] = "Insufficient balance\n";
const char WITHDRAW_FAILED[] = "Withdraw failed\n";
const char TRANSACTION_LIMIT_EXCEED[] = "Transaction limit exceeded";
const char NO_ACCOUNTS_FOUND[] = "No accounts found for Customer ID: ";
const char NO_TRANSACTIONS[] = "No transactions yet\n";
const char MINI_STATEMENT[] = "Mini Statement(Last 5 transactions):\n";
const char BANK_STATEMENT[] = "Bank Statement:\n";
const char RETURNING[] = "Returning...\n";
const char LOGGING_OUT[] = "Logging out...\n";
const char REQUEST_SENT[] = "Request sent successfully!\n";
const char REQUEST_FAILED[] = "Request queue is full!\n";
const char CUSTOMER_NOT_FOUND[] = "Customer not found\n";
const char CREATED_ACCOUNT[] = ". Created accounts: ";
const char ACCOUNT_CREATED[] = "Account created successfully!\n";
const char ACCOUNT_FAILED[] = "Failed to create account (max limit reached)\n";
const char CUSTOMER_CREATED[] = "Customer created successfully!\n";
const char YOUR_CUSTOMER_ID[] = "Your customer ID is: ";
const char ACCOUNT_REMOVED[] = "Account removed successfully!\n";
const char ACCOUNT_NOT_FOUND[] = "Account not found\n";
const char CUSTOMER_REMOVE_FAILED[] = "Customer with ID not found.\n";
const char CUSTOMER_REMOVE_SUCCESS[] = "Customer with ID removed successfully\n";
const char NO_ACCOUNTS[] = "No accounts yet\n";
const char NO_CUSTOMERS[] = "No customers yet\n";
const char NO_REQUESTS[] = "No pending account requests\n";
const char REQUESTS_PROCESSED[] = "Processed requests: ";
const char FAILED_REQUESTS[] = ", Failed: ";
const char REQUESTS_FAILED[] = "No accounts created. All requests failed.\n";
const char USER_MENU[] =
    "1. Signup\n2. Login\n3. Exit\nEnter your choice: ";
const char CUSTOMER_MENU[] =
    "1. Create Account\n2. Access Account\n3. Show my accounts\n4. Logout\nEnter choice: ";
const char ACCOUNT_MENU[] =
    "1. Deposit money\n2. Withdraw money\n3. Mini statement\n4. Bank statement\n5. Show Balance \n6. Back\nEnter choice: ";
const char ADMIN_MENU[] =
    "1. Create Account\n2. Close Account\n3. Show All Customers\n4. Show all accounts\n5. Remove Customer\n6. Process account requests\n7. Logout\nEnter choice: ";
const char CUSTOMER[] = "customer";
const char BALANCE[] = "Balance: ";
const char ADMIN[] = "admin";
const char CUSTOMER_ID_LABEL[] = "Customer id: ";
const char NAME_LABEL[] = " | Name: ";
const char ACCOUNT_NUMBER_LABEL[] = "Account Number: ";
const char BALANCE_LABEL[] = " | Balance: ";
const char ACCOUNT_OWNER_ID_LABEL[] = " | Customer Id: ";
const char ACCOUNT_TYPE_LABEL[] = " | Account Type: ";
const char ACCOUNT_NUMBER_CUSTOMER_ID[] = "Account Number for customer ID ";
const char IS_LABEL[] = " is: ";
const char TRANSACTION_ID_LABEL[] = "Transaction Id: ";
const char TRANSACTION_ACCOUNT_NUMBER_LABEL[] = " | Account Number: ";
const char TRANSACTION_TYPE_LABEL[] = " | Transaction type: ";
const char TRANSACTION_AMOUNT_LABEL[] = " | Amount: ";
const char ACCOUNT_NO_LABEL[] = "Account No: ";
const char TYPE_LABEL[] = " | Type: ";
const char CUSTOMER_WITH_ID_PREFIX[] = "Customer with ID ";
const char CUSTOMER_WITH_ID_NOT_FOUND_SUFFIX[] = " not found.\n";
const char CUSTOMER_WITH_ID_REMOVED_SUFFIX[] = " removed successfully\n";

const DefaultAdmin DEFAULT_ADMINS[] = {
    {"Admin1", "admin123"},
    {"Admin2", "admin234"},
    {"Admin3", "admin345"}};
const int DEFAULT_ADMIN_COUNT = sizeof(DEFAULT_ADMINS) / sizeof(DefaultAdmin);

#endif
