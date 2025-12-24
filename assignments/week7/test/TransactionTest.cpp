#include <gtest/gtest.h>
#include "Transaction.h"

TEST(TransactionTest, ConstructorAndGetters)
{
    Transaction transaction(101, 12, "deposit", 500);

    EXPECT_EQ(transaction.getTransactionId(), 101);
    EXPECT_EQ(transaction.getAccountNumber(), 12);
    EXPECT_EQ(transaction.getType(), "deposit");
    EXPECT_EQ(transaction.getAmount(), 500);
}
