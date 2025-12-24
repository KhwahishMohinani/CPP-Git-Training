#include <gtest/gtest.h>
#include "Account.h"
#include "Transaction.h"

class AccountTest : public ::testing::Test
{
protected:
    Account *account;

    void SetUp() override
    {
        account = new Account(1, 1000.0, "savings", 101);
    }

    void TearDown() override
    {
        delete account;
    }
};

TEST_F(AccountTest, GettersReturnCorrectValues)
{
    EXPECT_EQ(account->getAccountNumber(), 1);
    EXPECT_EQ(account->getBalance(), 1000.0);
    EXPECT_EQ(account->getAccountType(), "savings");
    EXPECT_EQ(account->getCustomerId(), 101);
    EXPECT_EQ(account->getTransactionsCount(), 0);
}

TEST_F(AccountTest, AddBalanceUpdatesBalanceAndTransaction)
{
    bool success = account->addBalance(500.0);
    EXPECT_TRUE(success);
    EXPECT_EQ(account->getBalance(), 1500.0);
    EXPECT_EQ(account->getTransactionsCount(), 1);

    Transaction *t = account->getTransactions()[0];
    EXPECT_EQ(t->getType(), "deposit");
    EXPECT_EQ(t->getAmount(), 500);
}

TEST_F(AccountTest, SubtractBalanceUpdatesBalanceAndTransaction)
{
    bool success = account->subtractBalance(400.0);
    EXPECT_TRUE(success);
    EXPECT_EQ(account->getBalance(), 600.0);
    EXPECT_EQ(account->getTransactionsCount(), 1);

    Transaction *t = account->getTransactions()[0];
    EXPECT_EQ(t->getType(), "withdraw");
    EXPECT_EQ(t->getAmount(), 400);
}

TEST_F(AccountTest, AddTransactionFailsAfterMaxLimit)
{
    for (int i = 0; i < MAX_TRANSACTIONS; i++)
    {
        account->addBalance(10);
    }
    bool success = account->addBalance(10);
    EXPECT_FALSE(success);
    EXPECT_EQ(account->getTransactionsCount(), MAX_TRANSACTIONS);
}
