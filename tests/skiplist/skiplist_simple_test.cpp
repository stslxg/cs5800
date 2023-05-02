#include <gtest/gtest.h>
#include "skiplist/skiplist.hpp"

TEST(TestSkipListSimple, TestEmpty) {
    SkipList L;
    EXPECT_FALSE(L.lookup(0));
}

TEST(TestSkipListSimple, TestInsert) {
    SkipList L;
    L.insert(0);
    EXPECT_TRUE(L.lookup(0));
}

TEST(TestSkipListSimple, TestInsertTwoKeys) {
    SkipList L;
    L.insert(0);
    L.insert(1);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));

    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
}

TEST(TestSkipListSimple, TestDelete) {
    SkipList L;
    L.insert(0);
    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.del(0));
    EXPECT_FALSE(L.lookup(0));
}

TEST(TestSkipListSimple, TestDeleteEmpty) {
    SkipList L;
    EXPECT_FALSE(L.del(0));
}

TEST(TestSkipListSimple, TestInsertDelete) {
    SkipList L;
    L.insert(0);
    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.del(0));
    EXPECT_FALSE(L.lookup(0));
    L.insert(0);
    EXPECT_TRUE(L.lookup(0));
}
