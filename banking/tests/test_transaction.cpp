#include <gtest/gtest.h>
#include <stdexcept>
#include "Transaction.h"
#include "Account.h"

TEST(TransactionTest, DefaultFee) {
    Transaction tx;
    EXPECT_EQ(tx.fee(), 1);
}

TEST(TransactionTest, SetFee) {
    Transaction tx;
    tx.set_fee(10);
    EXPECT_EQ(tx.fee(), 10);
}

TEST(TransactionTest, Make_SameAccount_Throws) {
    Transaction tx;
    Account acc(1, 100);
    EXPECT_THROW(tx.Make(acc, acc, 200), std::logic_error);
}

TEST(TransactionTest, Make_NegativeSum_Throws) {
    Transaction tx;
    Account from(1, 100), to(2, 100);
    EXPECT_THROW(tx.Make(from, to, -10), std::invalid_argument);
}

TEST(TransactionTest, Make_SumLessThan100_Throws) {
    Transaction tx;
    Account from(1, 100), to(2, 100);
    EXPECT_THROW(tx.Make(from, to, 99), std::logic_error);
}

TEST(TransactionTest, Make_FeeTooHigh_ReturnsFalse) {
    Transaction tx;
    tx.set_fee(60); 
    Account from(1, 1000), to(2, 100);
    EXPECT_FALSE(tx.Make(from, to, 100));
    EXPECT_EQ(from.GetBalance(), 1000);
    EXPECT_EQ(to.GetBalance(), 100);
}

TEST(TransactionTest, Make_Success) {
    Transaction tx;
    Account from(1, 1000), to(2, 200);
    
    bool res = tx.Make(from, to, 200);
    
    EXPECT_TRUE(res);
    EXPECT_EQ(from.GetBalance(), 1000); 
    EXPECT_EQ(to.GetBalance(), 199);
}

TEST(TransactionTest, Make_RollbackOnFail) {
    Transaction tx;
    Account from(1, 1000), to(2, 0); 
    
    bool res = tx.Make(from, to, 100);
    
    EXPECT_FALSE(res);
    EXPECT_EQ(to.GetBalance(), 0);
    EXPECT_EQ(from.GetBalance(), 1000);
}

TEST(TransactionTest, Make_UnlockOnException) {
    Transaction tx;
    Account from(1, 1000), to(2, 100);
    
    try {
        tx.Make(from, to, 50); 
    } catch (...) {}
    
    EXPECT_NO_THROW(from.Lock());
    from.Unlock();
    EXPECT_NO_THROW(to.Lock());
    to.Unlock();
}
