#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IAccount.h"

class MockAccount : public IAccount
{
public:
    MOCK_METHOD(long, getAccountNumber, (), (const));
    MOCK_METHOD((std::string), getAccountType, (), (const));
    MOCK_METHOD(int, getCustomerId, (), (const));
    MOCK_METHOD(double, getBalance, (), (const));
    MOCK_METHOD(bool, addBalance, (double amount));
    MOCK_METHOD(bool, subtractBalance, (double amount));
    MOCK_METHOD(Transaction **, getTransactions, ());
    MOCK_METHOD(int, getTransactionsCount, (), (const));
};
