#include <gtest/gtest.h>
#include "User.h"

TEST(UserTest, ConstructorAndGetters)
{
    User user("Alice", 101, "pass123", "customer");

    EXPECT_EQ(user.getName(), "Alice");
    EXPECT_EQ(user.getUserId(), 101);
    EXPECT_EQ(user.getPassword(), "pass123");
    EXPECT_EQ(user.getUserType(), "customer");
}
