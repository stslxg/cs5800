#include <gtest/gtest.h>
#include "hash.hpp"

TEST(TestHash, TestInsert) {
    Hash hash_table(1000);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);

    EXPECT_EQ(hash_table.find("hello"), 2);
    EXPECT_EQ(hash_table.find("world"), 2);
    EXPECT_EQ(hash_table.find("helloworld"), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
