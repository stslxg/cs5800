#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "hash.hpp"

class MockHashForInsert: public Hash {
public:
    MOCK_METHOD(void, insert, (const std::string&, int), (override));
};

TEST(TestHashWithMock, TestIncrease) {
    MockHashForInsert hash_table;
    EXPECT_CALL(hash_table, insert("hello", 1)).Times(1);
    hash_table.increase("hello");
}

class MockHashForHash: public Hash {
public:
    MOCK_METHOD(int, hash, (const std::string&), (const, override));
    MockHashForHash(): Hash{ 2 } {};
};

class MockHashForHashFixture: public ::testing::Test {
public:
    MockHashForHash hash_table;
    void SetUp() override;
};

void MockHashForHashFixture::SetUp() {
    EXPECT_CALL(hash_table, hash(testing::_)).WillRepeatedly(testing::Return(0));
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("a", 1);
}

TEST_F(MockHashForHashFixture, TestDelete) {
    hash_table.del("hello");
    EXPECT_EQ(0, hash_table.find("hello"));
    EXPECT_EQ(1, hash_table.find("world"));
    EXPECT_EQ(1, hash_table.find("a"));
}

TEST_F(MockHashForHashFixture, TestHist) {
    std::map<int, int> hist = hash_table.hist();
    EXPECT_EQ(2, hist.size());
    EXPECT_EQ(1, hist[0]);
    EXPECT_EQ(1, hist[3]);
}