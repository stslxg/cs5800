#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "skiplist/skiplist.hpp"

class MockSkipList: public SkipList {
public:
    MOCK_METHOD(int, get_rand_bit, (), (override));
};

TEST(TestSkipListInsert, TestInsertTwoNodesInOneLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillRepeatedly(testing::Return(0));
    L.insert(0);
    L.insert(1);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));

    EXPECT_EQ(1, L.search(0)->next.size());
    EXPECT_EQ(1, L.search(1)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
}

TEST(TestSkipListInsert, TestInsertThreeNodesInOneLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillRepeatedly(testing::Return(0));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(1, L.search(0)->next.size());
    EXPECT_EQ(1, L.search(1)->next.size());
    EXPECT_EQ(1, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
}

int MockGetRandBitForTwoLevels() {
    static int i = 0;
    i = 1 - i;
    return i;
}

TEST(TestSkipListInsert, TestInsertTwoNodesInTwoLevels) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillRepeatedly(testing::Invoke(MockGetRandBitForTwoLevels));
    L.insert(0);
    L.insert(1);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));

    EXPECT_EQ(2, L.search(0)->next.size());
    EXPECT_EQ(2, L.search(1)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(1), L.search(0)->next[1]);
}

TEST(TestSkipListInsert, TestInsertThreeNodesInTwoLevels) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillRepeatedly(testing::Invoke(MockGetRandBitForTwoLevels));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(2, L.search(0)->next.size());
    EXPECT_EQ(2, L.search(1)->next.size());
    EXPECT_EQ(2, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(1), L.search(0)->next[1]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
    EXPECT_EQ(L.search(2), L.search(1)->next[1]);
}

int MockGetRandBitForThreeLevels() {
    static int i = 0;
    i = (i + 1) % 3;
    return i > 0 ? 1 : 0;
}

TEST(TestSkipListInsert, TestInsertTwoNodesInThreeLevels) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillRepeatedly(testing::Invoke(MockGetRandBitForThreeLevels));
    L.insert(0);
    L.insert(1);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));

    EXPECT_EQ(3, L.search(0)->next.size());
    EXPECT_EQ(3, L.search(1)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(1), L.search(0)->next[1]);
    EXPECT_EQ(L.search(1), L.search(0)->next[2]);
}

TEST(TestSkipListInsert, TestInsertThreeNodesInThreeLevels) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillRepeatedly(testing::Invoke(MockGetRandBitForThreeLevels));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(3, L.search(0)->next.size());
    EXPECT_EQ(3, L.search(1)->next.size());
    EXPECT_EQ(3, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(1), L.search(0)->next[1]);
    EXPECT_EQ(L.search(1), L.search(0)->next[2]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
    EXPECT_EQ(L.search(2), L.search(1)->next[1]);
    EXPECT_EQ(L.search(2), L.search(1)->next[2]);
}

TEST(TestSkipListInsert, TestInsertFirstNodeInFirstLevelSecondNodeInSecondLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0));
    L.insert(0);
    L.insert(1);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));

    EXPECT_EQ(1, L.search(0)->next.size());
    EXPECT_EQ(2, L.search(1)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
}

TEST(TestSkipListInsert, TestInsertFirstNodeInSecondLevelSecondNodeInFirstLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(0));
    L.insert(0);
    L.insert(1);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));

    EXPECT_EQ(2, L.search(0)->next.size());
    EXPECT_EQ(1, L.search(1)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_NE(L.search(1), L.search(0)->next[1]);
}

TEST(TestSkipListInsert, TestInsertFirstNodeInSecondLevelSecondNodeInFirstLevelThirdNodeInSecondLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(2, L.search(0)->next.size());
    EXPECT_EQ(1, L.search(1)->next.size());
    EXPECT_EQ(2, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(2), L.search(0)->next[1]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
}

TEST(TestSkipListInsert, TestInsertFirstNodeInThirdLevelSecondNodeInFirstLevelThirdNodeInThirdLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(3, L.search(0)->next.size());
    EXPECT_EQ(1, L.search(1)->next.size());
    EXPECT_EQ(3, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(2), L.search(0)->next[1]);
    EXPECT_EQ(L.search(2), L.search(0)->next[2]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
}

TEST(TestSkipListInsert, TestInsertFirstNodeInSecondLevelSecondNodeInFirstLevelThirdNodeInThirdLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(2, L.search(0)->next.size());
    EXPECT_EQ(1, L.search(1)->next.size());
    EXPECT_EQ(3, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(2), L.search(0)->next[1]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
}

TEST(TestSkipListInsert, TestInsertFirstNodeInFirstLevelSecondNodeInSecondLevelThirdNodeInThirdLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(1, L.search(0)->next.size());
    EXPECT_EQ(2, L.search(1)->next.size());
    EXPECT_EQ(3, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
    EXPECT_EQ(L.search(2), L.search(1)->next[1]);
}

TEST(TestSkipListInsert, TestInsertFirstNodeInThirdLevelSecondNodeInFirstLevelThirdNodeInSecondLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(3, L.search(0)->next.size());
    EXPECT_EQ(1, L.search(1)->next.size());
    EXPECT_EQ(2, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(2), L.search(0)->next[1]);
    EXPECT_NE(L.search(2), L.search(0)->next[2]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
}

TEST(TestSkipListInsert, TestInsertFirstNodeInThirdLevelSecondNodeInSecondLevelThirdNodeInFirstLevel) {
    MockSkipList L;
    EXPECT_CALL(L, get_rand_bit()).WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(1))
                                  .WillOnce(testing::Return(0))
                                  .WillOnce(testing::Return(0));
    L.insert(0);
    L.insert(1);
    L.insert(2);

    EXPECT_TRUE(L.lookup(0));
    EXPECT_TRUE(L.lookup(1));
    EXPECT_TRUE(L.lookup(2));

    EXPECT_EQ(3, L.search(0)->next.size());
    EXPECT_EQ(2, L.search(1)->next.size());
    EXPECT_EQ(1, L.search(2)->next.size());
    EXPECT_EQ(L.search(1), L.search(0)->next[0]);
    EXPECT_EQ(L.search(1), L.search(0)->next[1]);
    EXPECT_NE(L.search(1), L.search(0)->next[2]);
    EXPECT_NE(L.search(2), L.search(0)->next[2]);
    EXPECT_EQ(L.search(2), L.search(1)->next[0]);
    EXPECT_NE(L.search(2), L.search(1)->next[1]);

}