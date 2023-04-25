#include <gtest/gtest.h>
#include "hash.hpp"

TEST(TestHash, TestInsert) {
    Hash hash_table(2);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);

    ASSERT_EQ(2, hash_table.find("hello"));
    ASSERT_EQ(2, hash_table.find("world"));
    ASSERT_EQ(0, hash_table.find("helloworld"));
}

TEST(TestHash, TestDelete) {
    Hash hash_table(2);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("a", 1);
    hash_table.insert("b", 1);
    hash_table.insert("c", 1);
    hash_table.insert("d", 1);

    hash_table.del("hello");

    ASSERT_EQ(0, hash_table.find("hello"));
    ASSERT_EQ(2, hash_table.find("world"));
    ASSERT_EQ(1, hash_table.find("a"));
    ASSERT_EQ(1, hash_table.find("b"));
    ASSERT_EQ(1, hash_table.find("c"));
    ASSERT_EQ(1, hash_table.find("d"));
}

TEST(TestHash, TestEmptyHash) {
    Hash hash_table(2);
    ASSERT_EQ(0, hash_table.find("hello"));
    ASSERT_EQ(0, hash_table.find("world"));
}

