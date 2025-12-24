#include "IBank.h"
#include "Admin.h"
#include "MockBank.h"
#include "MockAccount.h"
#include "IAccount.h"
#include "Customer.h"
#include <gtest/gtest.h>

class AdminTest : public testing::Test
{
protected:
    Admin *admin;
    MockBank mockBank;

    void SetUp()
    {
        admin = new Admin("adminName", 5, "adminPassword", "admin", mockBank);
    }

    void TearDown()
    {
        delete admin;
    }
};

TEST_F(AdminTest, CreateAccount_ReturnsAccountNumber)
{
    Customer customer("Misty", 1, "pass", "customer");
    EXPECT_CALL(mockBank, addAccount(::testing::Ref(customer), testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockBank, getNextAccountId()).WillOnce(::testing::Return(1));

    long accountNumber = admin->createAccount(customer, 1200, "savings");
    EXPECT_EQ(accountNumber, 1);
}

TEST_F(AdminTest, CreateAccount_AddAccountFails)
{
    Customer customer("Brock", 2, "pass", "customer");

    EXPECT_CALL(mockBank, getNextAccountId()).WillOnce(::testing::Return(2));
    EXPECT_CALL(mockBank, addAccount(::testing::Ref(customer), testing::_)).WillOnce(::testing::Return(false));

    long accountNumber = admin->createAccount(customer, 2000, "savings");

    EXPECT_EQ(accountNumber, -1);
}

TEST_F(AdminTest, HandleRequests_AllSuccessful)
{
    Customer *customer = new Customer("Serena", 1, "pass", "customer");
    AccountRequest request{1, 4000, "current"};
    AccountRequest *requests[] = {&request};

    EXPECT_CALL(mockBank, getAllRequests()).WillOnce(::testing::Return(requests));
    EXPECT_CALL(mockBank, getRequestCount()).WillOnce(::testing::Return(1));
    EXPECT_CALL(mockBank, getCustomerById(request.customerId)).WillOnce(::testing::Return(customer));
    EXPECT_CALL(mockBank, getNextAccountId()).WillOnce(::testing::Return(10));
    EXPECT_CALL(mockBank, addAccount(::testing::Ref(*customer), testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockBank, clearRequests()).Times(1);

    bool status = admin->handleRequests();
    RequestResult result = admin->getLastResult();

    EXPECT_TRUE(status);
    EXPECT_EQ(result.processedCount, 1);
    EXPECT_EQ(result.createdCount, 1);
    EXPECT_EQ(result.failedCount, 0);
}

TEST_F(AdminTest, HandleRequests_CustomerNotFound)
{
    AccountRequest request{1, 4000, "current"};
    AccountRequest *requests[] = {&request};

    EXPECT_CALL(mockBank, getAllRequests()).WillOnce(::testing::Return(requests));
    EXPECT_CALL(mockBank, getRequestCount()).WillOnce(::testing::Return(1));
    EXPECT_CALL(mockBank, getCustomerById(request.customerId)).WillOnce(::testing::Return(nullptr));
    EXPECT_CALL(mockBank, clearRequests()).Times(1);

    bool status = admin->handleRequests();
    RequestResult result = admin->getLastResult();

    EXPECT_FALSE(status);
    EXPECT_EQ(result.processedCount, 1);
    EXPECT_EQ(result.createdCount, 0);
    EXPECT_EQ(result.failedCount, 1);
}

TEST_F(AdminTest, HandleRequests_MixedResults)
{
    Customer *customer = new Customer("May", 1, "pass", "customer");
    AccountRequest request1{1, 1000, "savings"};
    AccountRequest request2{2, 2000, "current"};
    AccountRequest *requests[] = {&request1, &request2};

    EXPECT_CALL(mockBank, getAllRequests()).WillOnce(::testing::Return(requests));
    EXPECT_CALL(mockBank, getRequestCount()).WillOnce(::testing::Return(2));
    EXPECT_CALL(mockBank, getCustomerById(1)).WillOnce(::testing::Return(customer));
    EXPECT_CALL(mockBank, getCustomerById(2)).WillOnce(::testing::Return(nullptr));
    EXPECT_CALL(mockBank, getNextAccountId()).WillOnce(::testing::Return(101));
    EXPECT_CALL(mockBank, addAccount(::testing::Ref(*customer), testing::_)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockBank, clearRequests()).Times(1);

    bool status = admin->handleRequests();
    RequestResult result = admin->getLastResult();

    EXPECT_TRUE(status);
    EXPECT_EQ(result.processedCount, 2);
    EXPECT_EQ(result.createdCount, 1);
    EXPECT_EQ(result.failedCount, 1);
}

TEST_F(AdminTest, HandleRequests_NoRequests)
{
    EXPECT_CALL(mockBank, getAllRequests()).WillOnce(::testing::Return(nullptr));
    EXPECT_CALL(mockBank, getRequestCount()).WillOnce(::testing::Return(0));
    EXPECT_CALL(mockBank, clearRequests()).Times(1);

    bool status = admin->handleRequests();
    RequestResult result = admin->getLastResult();

    EXPECT_FALSE(status);
    EXPECT_EQ(result.processedCount, 0);
    EXPECT_EQ(result.createdCount, 0);
    EXPECT_EQ(result.failedCount, 0);
}
