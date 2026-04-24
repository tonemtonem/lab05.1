#include <gtest/gtest.h>
#include <stdexcept>
#include "Account.h"

TEST(AccountTest, Constructor_InitializesCorrectly) {
    Account acc(1, 100);
    EXPECT_EQ(acc.id(), 1);
    EXPECT_EQ(acc.GetBalance(), 100);
}

TEST(AccountTest, Lock_Success) {
    Account acc(1, 100);
    EXPECT_NO_THROW(acc.Lock());
}

TEST(AccountTest, Lock_ThrowsIfAlreadyLocked) {
    Account acc(1, 100);
    acc.Lock();
    EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(AccountTest, Unlock_Success) {
    Account acc(1, 100);
    acc.Lock();
    EXPECT_NO_THROW(acc.Unlock());
}

TEST(AccountTest, Unlock_Idempotent) {
    Account acc(1, 100);
    EXPECT_NO_THROW(acc.Unlock()); 
}

TEST(AccountTest, ChangeBalance_ThrowsIfUnlocked) {
    Account acc(1, 100);
    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
    EXPECT_EQ(acc.GetBalance(), 100);
}

TEST(AccountTest, ChangeBalance_AddsWhenLocked) {
    Account acc(1, 100);
    acc.Lock();
    acc.ChangeBalance(50);
    EXPECT_EQ(acc.GetBalance(), 150);
}

TEST(AccountTest, ChangeBalance_SubtractsWhenLocked) {
    Account acc(1, 100);
    acc.Lock();
    acc.ChangeBalance(-30);
    EXPECT_EQ(acc.GetBalance(), 70);
}

TEST(AccountTest, ChangeBalance_ZeroWhenLocked) {
    Account acc(1, 100);
    acc.Lock();
    acc.ChangeBalance(0);
    EXPECT_EQ(acc.GetBalance(), 100);
}
