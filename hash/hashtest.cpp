#include <gtest/gtest.h>
#include <string>
#include <algorithm>
#include "hash.hpp"

TEST(TestHash, TestInsert) {
    Hash hash_table(2);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);

    ASSERT_EQ(1, hash_table.find("hello"));
    ASSERT_EQ(1, hash_table.find("world"));
    ASSERT_EQ(0, hash_table.find("helloworld"));
}

class HashSmallTestFixture: public ::testing::Test {
protected:
    void SetUp() override;
    Hash hash_table{ 2 };
};

class HashLargeTestFixture: public ::testing::Test {
protected:
    void SetUp() override;
    Hash hash_table{ 10 };
};

void HashSmallTestFixture::SetUp() {
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("a", 1);
    hash_table.insert("b", 1);
    hash_table.insert("c", 1);
    hash_table.insert("d", 1);
}

void HashLargeTestFixture::SetUp() {
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("a", 1);
    hash_table.insert("b", 1);
    hash_table.insert("c", 1);
    hash_table.insert("d", 1);
}


TEST_F(HashSmallTestFixture, TestMultipleInsert) {
    ASSERT_EQ(2, hash_table.find("hello"));
    ASSERT_EQ(2, hash_table.find("world"));
    ASSERT_EQ(1, hash_table.find("a"));
    ASSERT_EQ(1, hash_table.find("b"));
    ASSERT_EQ(1, hash_table.find("c"));
    ASSERT_EQ(1, hash_table.find("d"));
    ASSERT_EQ(0, hash_table.find("e"));
}

TEST_F(HashSmallTestFixture, TestDelete) {
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

TEST(TestHash, TestIncrease) {
    Hash hash_table(2);
    hash_table.increase("hello");
    hash_table.increase("world");
    hash_table.increase("hello");
    hash_table.increase("world");

    ASSERT_EQ(2, hash_table.find("hello"));
    ASSERT_EQ(2, hash_table.find("world"));
    ASSERT_EQ(0, hash_table.find("helloworld"));
}

TEST_F(HashLargeTestFixture, TestHist) {
    std::map<int, int> hist = hash_table.hist();

    int unique_word_count = 0;
    int list_count = 0;
    for (auto [len, count]: hist) {
        unique_word_count += len * count;
        list_count += count;
    }
    
    ASSERT_EQ(6, unique_word_count);
    ASSERT_EQ(10, list_count);
}

TEST(TestHash, TestHistEmpty) {
    Hash hash_table(100);
    std::map<int, int> hist = hash_table.hist();

    ASSERT_EQ(1, hist.size());
    ASSERT_EQ(100, hist[0]);
}

TEST_F(HashSmallTestFixture, TestListAllKeys) {
    std::vector<std::string> keys = hash_table.list_all_keys();

    ASSERT_EQ(6, keys.size());
    ASSERT_TRUE(std::find(keys.begin(), keys.end(), "hello") != keys.end());
    ASSERT_TRUE(std::find(keys.begin(), keys.end(), "world") != keys.end());
    ASSERT_TRUE(std::find(keys.begin(), keys.end(), "a") != keys.end());
    ASSERT_TRUE(std::find(keys.begin(), keys.end(), "b") != keys.end());
    ASSERT_TRUE(std::find(keys.begin(), keys.end(), "c") != keys.end());
    ASSERT_TRUE(std::find(keys.begin(), keys.end(), "d") != keys.end());

    ASSERT_FALSE(std::find(keys.begin(), keys.end(), "e") != keys.end());
}

TEST(TestHash, TestListAllKeysEmpty) {
    Hash hash_table(3);
    std::vector<std::string> keys = hash_table.list_all_keys();

    ASSERT_EQ(0, keys.size());
}

TEST_F(HashSmallTestFixture, TestList) {
    using namespace std::string_literals;

    std::vector<std::pair<std::string, int>> list = hash_table.list();

    ASSERT_EQ(6, list.size());
    ASSERT_TRUE(std::find(list.begin(), list.end(), std::make_pair("hello"s, 2)) != list.end());
    ASSERT_TRUE(std::find(list.begin(), list.end(), std::make_pair("world"s, 2)) != list.end());
    ASSERT_TRUE(std::find(list.begin(), list.end(), std::make_pair("a"s, 1)) != list.end());
    ASSERT_TRUE(std::find(list.begin(), list.end(), std::make_pair("b"s, 1)) != list.end());
    ASSERT_TRUE(std::find(list.begin(), list.end(), std::make_pair("c"s, 1)) != list.end());
    ASSERT_TRUE(std::find(list.begin(), list.end(), std::make_pair("d"s, 1)) != list.end());

    ASSERT_FALSE(std::find(list.begin(), list.end(), std::make_pair("e"s, 1)) != list.end());
}

TEST(TestHash, TestListEmpty) {
    Hash hash_table(3);
    std::vector<std::pair<std::string, int>> list = hash_table.list();

    ASSERT_EQ(0, list.size());
}
