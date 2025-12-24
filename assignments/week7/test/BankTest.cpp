#include "Bank.h"
#include "Customer.h"
#include "Account.h"
#include "Admin.h"
#include "MockAccount.h"
#include <gtest/gtest.h>

class BankTest : public ::testing::Test
{
protected:
    Bank *bank;
    void SetUp() override
    {
        bank = new Bank(1, "TestBank", "mainAdmin", "pass123");
    }

    void TearDown() override
    {
        delete bank;
    }
};

TEST_F(BankTest, ConstructorInitializesDefaults)
{
    EXPECT_GT(bank->getCustomersCount(), -1);
    EXPECT_GT(bank->getAccountsCount(), -1);
}

TEST_F(BankTest, DefaultAdminsCreated)
{
    EXPECT_EQ(bank->getAdminByCredentials(1, DEFAULT_ADMINS[0].password)->getUserType(), ADMIN);
}

TEST_F(BankTest, AddCustomerIncreasesCount)
{
    int before = bank->getCustomersCount();
    Customer *customer = bank->addCustomer("Ariel", "123");
    ASSERT_NE(customer, nullptr);
    EXPECT_EQ(bank->getCustomersCount(), before + 1);
}

TEST_F(BankTest, AddCustomer_FailsWhenFull)
{
    for (int i = 0; i < MAX_CUSTOMERS; i++)
    {
        Customer *customer = bank->addCustomer("Jane", "pass");
        ASSERT_NE(customer, nullptr);
    }
    Customer *extraCustomer = bank->addCustomer("Max", "pass");
    EXPECT_EQ(extraCustomer, nullptr);
}

TEST_F(BankTest, GetCustomerByIdWorks)
{
    Customer *customer = bank->addCustomer("Belle", "456");
    ASSERT_NE(customer, nullptr);
    Customer *foundCustomer = bank->getCustomerById(customer->getUserId());
    EXPECT_EQ(foundCustomer, customer);
}

TEST_F(BankTest, GetCustomerByCredentialsValidAndInvalid)
{
    Customer *customer = bank->addCustomer("Carol", "789");
    ASSERT_NE(customer, nullptr);
    EXPECT_NE(bank->getCustomerByCredentials(customer->getUserId(), "789"), nullptr);
    EXPECT_EQ(bank->getCustomerByCredentials(customer->getUserId(), "incorrect"), nullptr);
}

TEST_F(BankTest, AddAccount_Success_ReturnsTrue)
{
    Customer *customer = bank->addCustomer("Dawn", "pass");
    ASSERT_NE(customer, nullptr);

    MockAccount *mockAccount = new MockAccount();
    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(customer->getUserId()));

    ASSERT_TRUE(bank->addAccount(*customer, mockAccount));

    IAccount *retrieved = bank->getAccount(1, customer->getUserId());
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved, mockAccount);
}

TEST_F(BankTest, AddAccount_FailsWhenFull_ReturnsFalse)
{
    Customer *customer = bank->addCustomer("Dawn", "pass");
    ASSERT_NE(customer, nullptr);

    for (int i = 0; i < MAX_ACCOUNTS; i++)
    {
        MockAccount *mockAccount = new MockAccount();
        EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(i + 1));
        EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(customer->getUserId()));
        bank->addAccount(*customer, mockAccount);
    }

    MockAccount *extraAccount = new MockAccount();
    EXPECT_CALL(*extraAccount, getAccountNumber()).WillRepeatedly(testing::Return(999));
    EXPECT_CALL(*extraAccount, getCustomerId()).WillRepeatedly(testing::Return(customer->getUserId()));

    bool status = bank->addAccount(*customer, extraAccount);

    EXPECT_FALSE(status);
    EXPECT_EQ(bank->getAccountsCount(), MAX_ACCOUNTS);

    delete extraAccount;
}

TEST_F(BankTest, GetAccount_ReturnsMatchingAccount)
{
    Customer *customer = bank->addCustomer("Jane", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(1001));

    bank->addAccount(*customer, mockAccount);

    IAccount *found = bank->getAccount(1, 1001);

    EXPECT_EQ(found, mockAccount);
}

TEST_F(BankTest, GetAccount_ReturnsNullWhenNotFound)
{
    Customer *customer = bank->addCustomer("Lilly", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(10));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(2001));

    bank->addAccount(*customer, mockAccount);

    IAccount *found = bank->getAccount(99, 9999);
    EXPECT_EQ(found, nullptr);
}

TEST_F(BankTest, GetAccount_FindsCorrectAmongMultiple)
{
    Customer *customer = bank->addCustomer("Mia", "pass");
    ASSERT_NE(customer, nullptr);

    MockAccount *account1 = new MockAccount();
    MockAccount *account2 = new MockAccount();
    MockAccount *account3 = new MockAccount();

    EXPECT_CALL(*account1, getAccountNumber()).WillRepeatedly(testing::Return(11));
    EXPECT_CALL(*account1, getCustomerId()).WillRepeatedly(testing::Return(3001));

    EXPECT_CALL(*account2, getAccountNumber()).WillRepeatedly(testing::Return(22));
    EXPECT_CALL(*account2, getCustomerId()).WillRepeatedly(testing::Return(3001));

    EXPECT_CALL(*account3, getAccountNumber()).WillRepeatedly(testing::Return(33));
    EXPECT_CALL(*account3, getCustomerId()).WillRepeatedly(testing::Return(3001));

    bank->addAccount(*customer, account1);
    bank->addAccount(*customer, account2);
    bank->addAccount(*customer, account3);

    IAccount *found = bank->getAccount(22, 3001);

    EXPECT_EQ(found, account2);
}

TEST_F(BankTest, RemoveAccountSuccess_AccountFound)
{
    Customer *customer = bank->addCustomer("Grace", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(1));

    bank->addAccount(*customer, mockAccount);

    int beforeAccountsCount = bank->getAccountsCount();
    bool status = bank->removeAccount(1, 1);
    int afterAccountsCount = bank->getAccountsCount();

    EXPECT_TRUE(status);
    EXPECT_EQ(beforeAccountsCount - 1, afterAccountsCount);
}

TEST_F(BankTest, RemoveAccountFail_AccountNotFound)
{
    Customer *customer = bank->addCustomer("Grace", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(1));

    bank->addAccount(*customer, mockAccount);

    int beforeCount = bank->getAccountsCount();
    bool status = bank->removeAccount(999, 1);
    int afterCount = bank->getAccountsCount();

    EXPECT_FALSE(status);
    EXPECT_EQ(afterCount, beforeCount);
}

TEST_F(BankTest, RemoveAccount_LastAccount)
{
    Customer *customer = bank->addCustomer("Grace", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(1));

    bank->addAccount(*customer, mockAccount);

    bool status = bank->removeAccount(1, 1);

    EXPECT_TRUE(status);
    EXPECT_EQ(bank->getAccountsCount(), 0);
    EXPECT_EQ(bank->getAccount(1, 1), nullptr);
}

TEST_F(BankTest, RemoveAccountsByCustomerId_RemovesAllMatching)
{
    Customer *customer1 = bank->addCustomer("Jasmine", "pass");
    ASSERT_NE(customer1, nullptr);
    Customer *customer2 = bank->addCustomer("Jack", "pass");
    ASSERT_NE(customer2, nullptr);

    MockAccount *mockAccount1 = new MockAccount();
    MockAccount *mockAccount2 = new MockAccount();
    MockAccount *mockAccount3 = new MockAccount();

    EXPECT_CALL(*mockAccount1, getCustomerId()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount2, getCustomerId()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount3, getCustomerId()).WillRepeatedly(testing::Return(2));

    EXPECT_CALL(*mockAccount1, getAccountNumber()).WillRepeatedly(testing::Return(101));
    EXPECT_CALL(*mockAccount2, getAccountNumber()).WillRepeatedly(testing::Return(102));
    EXPECT_CALL(*mockAccount3, getAccountNumber()).WillRepeatedly(testing::Return(201));

    bank->addAccount(*customer1, mockAccount1);
    bank->addAccount(*customer1, mockAccount2);
    bank->addAccount(*customer2, mockAccount3);

    EXPECT_EQ(bank->getAccountsCount(), 3);

    bank->removeAccountsByCustomerId(1);

    EXPECT_EQ(bank->getAccountsCount(), 1);
    IAccount *remaining = bank->getAccount(201, 2);
    EXPECT_EQ(remaining, mockAccount3);

    EXPECT_EQ(bank->getAccount(101, 1), nullptr);
    EXPECT_EQ(bank->getAccount(102, 1), nullptr);
}

TEST_F(BankTest, RemoveAccountsByCustomerId_NoMatchingAccounts)
{
    Customer *customer = bank->addCustomer("Ivy", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *acc = new MockAccount();

    EXPECT_CALL(*acc, getCustomerId()).WillRepeatedly(testing::Return(4));
    EXPECT_CALL(*acc, getAccountNumber()).WillRepeatedly(testing::Return(401));

    bank->addAccount(*customer, acc);

    int before = bank->getAccountsCount();
    bank->removeAccountsByCustomerId(3);
    int after = bank->getAccountsCount();

    EXPECT_EQ(before, after);
}

TEST_F(BankTest, RemoveAccountsByCustomerId_EmptyBank)
{
    EXPECT_EQ(bank->getAccountsCount(), 0);
    bank->removeAccountsByCustomerId(1);
    EXPECT_EQ(bank->getAccountsCount(), 0);
}

TEST_F(BankTest, DepositSuccess_ReturnsDepositSuccessCode)
{
    Customer *customer = bank->addCustomer("Emily", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    bank->addAccount(*customer, mockAccount);

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, addBalance(1000)).WillOnce(testing::Return(true));

    int errorCode = bank->deposit(1, 1, 1000);

    EXPECT_EQ(errorCode, DEPOSIT_SUCCESS_CODE);
}

TEST_F(BankTest, DepositFails_ReturnsTransactionLimitExceededCode)
{
    Customer *customer = bank->addCustomer("Flora", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, addBalance(5000)).WillOnce(testing::Return(false));

    bank->addAccount(*customer, mockAccount);

    int errorCode = bank->deposit(1, 1, 5000);
    EXPECT_EQ(errorCode, TRANSACTION_LIMIT_EXCEEDED);
}

TEST_F(BankTest, DepositFails_ReturnsAccountNotFoundCode)
{
    int errorCode = bank->deposit(99, 1, 1000);
    EXPECT_EQ(errorCode, ACCOUNT_NOT_FOUND_CODE);
}

TEST_F(BankTest, Withdraw_Success_ReturnsSuccessCode)
{
    Customer *customer = bank->addCustomer("Alice", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(101));
    EXPECT_CALL(*mockAccount, getBalance()).WillRepeatedly(testing::Return(1000));
    EXPECT_CALL(*mockAccount, subtractBalance(500)).WillOnce(testing::Return(true));

    bank->addAccount(*customer, mockAccount);

    int result = bank->withdraw(1, 101, 500);
    EXPECT_EQ(result, WITHDRAW_SUCCESS_CODE);
}

TEST_F(BankTest, Withdraw_Fails_InsufficientBalance)
{
    Customer *customer = bank->addCustomer("Bob", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(2));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(102));
    EXPECT_CALL(*mockAccount, getBalance()).WillRepeatedly(testing::Return(300));

    bank->addAccount(*customer, mockAccount);

    int result = bank->withdraw(2, 102, 500);
    EXPECT_EQ(result, INSUFFICIENT_BALANCE_CODE);
}

TEST_F(BankTest, Withdraw_Fails_TransactionLimitExceeded)
{
    Customer *customer = bank->addCustomer("Carol", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(3));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(103));
    EXPECT_CALL(*mockAccount, getBalance()).WillRepeatedly(testing::Return(1000));
    EXPECT_CALL(*mockAccount, subtractBalance(500)).WillOnce(testing::Return(false));

    bank->addAccount(*customer, mockAccount);

    int result = bank->withdraw(3, 103, 500);
    EXPECT_EQ(result, TRANSACTION_LIMIT_EXCEEDED);
}

TEST_F(BankTest, Withdraw_Fails_AccountNotFound)
{
    int result = bank->withdraw(999, 101, 100);
    EXPECT_EQ(result, ACCOUNT_NOT_FOUND_CODE);
}

TEST_F(BankTest, RemoveCustomerById_RemovesExistingCustomer)
{
    Customer *customer1 = bank->addCustomer("George", "pass");
    Customer *customer2 = bank->addCustomer("Hank", "pass");
    Customer *customer3 = bank->addCustomer("Ivy", "pass");

    int beforeCount = bank->getCustomersCount();

    bank->removeCustomerById(customer2->getUserId());

    EXPECT_EQ(bank->getCustomersCount(), beforeCount - 1);
    EXPECT_EQ(bank->getCustomerById(customer2->getUserId()), nullptr);
    EXPECT_NE(bank->getCustomerById(customer1->getUserId()), nullptr);
    EXPECT_NE(bank->getCustomerById(customer3->getUserId()), nullptr);
}

TEST_F(BankTest, RemoveCustomerById_NonExistentCustomer_NoChange)
{
    Customer *customer = bank->addCustomer("Charlie", "pass");
    int beforeCount = bank->getCustomersCount();

    bank->removeCustomerById(999);
    EXPECT_EQ(bank->getCustomersCount(), beforeCount);
    EXPECT_NE(bank->getCustomerById(customer->getUserId()), nullptr);
}

TEST_F(BankTest, GetAccountsByCustomerId_ReturnsAllCustomerAccounts)
{
    Customer *customer1 = bank->addCustomer("Bob", "pass");
    ASSERT_NE(customer1, nullptr);
    Customer *customer2 = bank->addCustomer("Eve", "pass");
    ASSERT_NE(customer2, nullptr);
    MockAccount *mockAccount1 = new MockAccount();
    MockAccount *mockAccount2 = new MockAccount();
    MockAccount *mockAccount3 = new MockAccount();

    EXPECT_CALL(*mockAccount1, getCustomerId()).WillRepeatedly(testing::Return(200));
    EXPECT_CALL(*mockAccount2, getCustomerId()).WillRepeatedly(testing::Return(200));
    EXPECT_CALL(*mockAccount3, getCustomerId()).WillRepeatedly(testing::Return(999));

    EXPECT_CALL(*mockAccount1, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount2, getAccountNumber()).WillRepeatedly(testing::Return(2));
    EXPECT_CALL(*mockAccount3, getAccountNumber()).WillRepeatedly(testing::Return(3));

    bank->addAccount(*customer1, mockAccount1);
    bank->addAccount(*customer1, mockAccount2);
    bank->addAccount(*customer2, mockAccount3);

    int accountCount = 0;
    IAccount **accounts = bank->getAccountsByCustomerId(200, accountCount);

    EXPECT_EQ(accountCount, 2);
    EXPECT_NE(accounts, nullptr);
    delete[] accounts;
}

TEST_F(BankTest, GetAccountsByCustomerId_NoMatches_ReturnsEmptyArray)
{
    Customer *customer = bank->addCustomer("Catherine", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(301));
    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(10));

    bank->addAccount(*customer, mockAccount);

    int accountCount = 0;
    IAccount **accounts = bank->getAccountsByCustomerId(9999, accountCount);

    EXPECT_EQ(accountCount, 0);
    EXPECT_NE(accounts, nullptr);

    delete[] accounts;
}

TEST_F(BankTest, GetAccountsByCustomerId_NoAccountsFound)
{
    bank->addCustomer("Tori", "pass");
    int accountCount = 0;
    IAccount **accounts = bank->getAccountsByCustomerId(1, accountCount);

    EXPECT_EQ(accountCount, 0);
    EXPECT_NE(accounts, nullptr);
    delete[] accounts;
}

TEST_F(BankTest, GetAdminByCredentials_Valid_ReturnsAdmin)
{
    Admin *admin = bank->getAdminByCredentials(1, DEFAULT_ADMINS[0].password);
    ASSERT_NE(admin, nullptr);
    EXPECT_EQ(admin->getUserId(), 1);
    EXPECT_EQ(admin->getPassword(), DEFAULT_ADMINS[0].password);
}

TEST_F(BankTest, GetAdminByCredentials_WrongPassword_ReturnsNull)
{
    Admin *admin = bank->getAdminByCredentials(1, "wrongpass");
    EXPECT_EQ(admin, nullptr);
}

TEST_F(BankTest, GetAdminByCredentials_WrongId_ReturnsNull)
{
    Admin *admin = bank->getAdminByCredentials(999, DEFAULT_ADMINS[0].password);
    EXPECT_EQ(admin, nullptr);
}

TEST_F(BankTest, GetAccountBalance_ReturnsCorrectBalance)
{
    Customer *customer = bank->addCustomer("Elina", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(101));
    EXPECT_CALL(*mockAccount, getBalance()).WillOnce(testing::Return(1234.56));

    bank->addAccount(*customer, mockAccount);

    double balance = bank->getAccountBalance(1, 101);
    EXPECT_EQ(balance, 1234.56);
}

TEST_F(BankTest, GetAccountTransactions_ReturnsCorrectPointer)
{
    Customer *customer = bank->addCustomer("Ken", "pass");
    ASSERT_NE(customer, nullptr);
    MockAccount *mockAccount = new MockAccount();
    Transaction **mockTransactions = new Transaction *[1];

    EXPECT_CALL(*mockAccount, getAccountNumber()).WillRepeatedly(testing::Return(2));
    EXPECT_CALL(*mockAccount, getCustomerId()).WillRepeatedly(testing::Return(102));
    EXPECT_CALL(*mockAccount, getTransactions()).WillOnce(testing::Return(mockTransactions));

    bank->addAccount(*customer, mockAccount);

    Transaction **transactions = bank->getAccountTransactions(2, 102);
    EXPECT_EQ(transactions, mockTransactions);

    delete[] mockTransactions;
}

TEST_F(BankTest, AddAccountRequest_Success_ReturnsTrue)
{
    int beforeCount = bank->getRequestCount();
    bool result = bank->addAccountRequest(101, 500.0, "savings");

    EXPECT_TRUE(result);
    EXPECT_EQ(bank->getRequestCount(), beforeCount + 1);

    AccountRequest *request = bank->getAllRequests()[beforeCount];
    EXPECT_EQ(request->customerId, 101);
    EXPECT_EQ(request->initialBalance, 500.0);
    EXPECT_EQ(request->accountType, "savings");
}

TEST_F(BankTest, AddAccountRequest_Fails_WhenFull_ReturnsFalse)
{
    for (int i = 0; i < MAX_REQUESTS; i++)
    {
        bank->addAccountRequest(i, 100.0, "savings");
    }

    bool result = bank->addAccountRequest(101, 1000.0, "current");
    EXPECT_FALSE(result);
    EXPECT_EQ(bank->getRequestCount(), MAX_REQUESTS);
}

TEST_F(BankTest, GetRequestCount_InitiallyZero)
{
    EXPECT_EQ(bank->getRequestCount(), 0);
}

TEST_F(BankTest, GetAllRequests_InitiallyEmpty)
{
    EXPECT_EQ(bank->getAllRequests(), bank->getAllRequests());
    EXPECT_EQ(bank->getRequestCount(), 0);
}

TEST_F(BankTest, GetAllRequests_ReturnsCorrectArrayAfterAdding)
{
    bank->addAccountRequest(101, 500, "savings");
    bank->addAccountRequest(102, 1000, "current");

    AccountRequest **requests = bank->getAllRequests();
    int count = bank->getRequestCount();

    EXPECT_EQ(count, 2);
    EXPECT_EQ(requests[0]->customerId, 101);
    EXPECT_EQ(requests[0]->initialBalance, 500);
    EXPECT_EQ(requests[0]->accountType, "savings");

    EXPECT_EQ(requests[1]->customerId, 102);
    EXPECT_EQ(requests[1]->initialBalance, 1000);
    EXPECT_EQ(requests[1]->accountType, "current");
}

TEST_F(BankTest, ClearRequests_RemovesAllRequests)
{
    bank->addAccountRequest(101, 500, "savings");
    bank->addAccountRequest(102, 1000, "current");

    int countBefore = bank->getRequestCount();
    EXPECT_EQ(countBefore, 2);

    bank->clearRequests();

    EXPECT_EQ(bank->getRequestCount(), 0);

    AccountRequest **requests = bank->getAllRequests();
    for (int i = 0; i < 2; i++)
    {
        EXPECT_EQ(requests[i], nullptr);
    }
}
