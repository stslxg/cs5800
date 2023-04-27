#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "hash.hpp"

class MockHash: public Hash {
public:
    MOCK_METHOD(void, insert, (const std::string&, int), (override));
};

TEST(TestHashWithMock, TestIncrease) {
    MockHash hash_table;
    EXPECT_CALL(hash_table, insert("hello", 1)).Times(1);
    hash_table.increase("hello");
}