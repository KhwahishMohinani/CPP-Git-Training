#include <gmock/gmock.h>
#include "IBank.h"

class MockBank : public IBank
{
public:
    MOCK_METHOD(int, getAccountsCount, (), (const));
    MOCK_METHOD(int, getCustomersCount, (), (const));
    MOCK_METHOD(int, getRequestCount, (), (const));
    MOCK_METHOD(int, getNextAccountId, (), (const));
    MOCK_METHOD(bool, addAccount, (Customer & customer, IAccount *account));
    MOCK_METHOD(bool, removeAccount, (long accountNumber, int customerId));
    MOCK_METHOD(IAccount *, getAccount, (long accountNumber, int customerId));
    MOCK_METHOD(IAccount **, getAllAccounts, ());
    MOCK_METHOD(Customer *, addCustomer, (const std::string &name, const std::string &password));
    MOCK_METHOD(Customer *, getCustomerById, (int id));
    MOCK_METHOD(Customer *, getCustomerByCredentials, (int id, const std::string &password));
    MOCK_METHOD(Admin *, getAdminByCredentials, (int id, const std::string &password));
    MOCK_METHOD(Customer **, getAllCustomers, ());
    MOCK_METHOD(void, removeAccountsByCustomerId, (int customerId));
    MOCK_METHOD(void, removeCustomerById, (int id));
    MOCK_METHOD(int, deposit, (long accountNumber, int customerId, double amount));
    MOCK_METHOD(int, withdraw, (long accountNumber, int customerId, double amount));
    MOCK_METHOD(Transaction **, getAccountTransactions, (long accountNumber, int userId));
    MOCK_METHOD(int, getAccountTransactionsCount, (long accountNumber, int userId));
    MOCK_METHOD(double, getAccountBalance, (long accountNumber, int customerId));
    MOCK_METHOD(bool, addAccountRequest, (int customerId, double balance, const std::string &type));
    MOCK_METHOD(AccountRequest **, getAllRequests, ());
    MOCK_METHOD(IAccount **, getAccountsByCustomerId, (int customerId, int &accountCount));
    MOCK_METHOD(void, clearRequests, ());
};
