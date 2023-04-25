#include <gtest/gtest.h>
#include <string>
#include <algorithm>
#include "hash.hpp"

TEST(TestHash, TestInsert) {
    Hash hash_table(2);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);

    EXPECT_EQ(1, hash_table.find("hello"));
    EXPECT_EQ(1, hash_table.find("world"));
    EXPECT_EQ(0, hash_table.find("helloworld"));
}

template <unsigned int M = 2>
class GenericHashTestFixture: public testing::Test {
protected:
    virtual void SetUp() override;
    Hash hash_table{ M };
};

template <unsigned int M>
void GenericHashTestFixture<M>::SetUp() {
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("hello", 1);
    hash_table.insert("world", 1);
    hash_table.insert("a", 1);
    hash_table.insert("b", 1);
    hash_table.insert("c", 1);
    hash_table.insert("d", 1);
}

using HashTestFixture = GenericHashTestFixture<2>;
using LargeHashTestFixture = GenericHashTestFixture<10>;

TEST_F(HashTestFixture, TestMultipleInsert) {
    EXPECT_EQ(2, hash_table.find("hello"));
    EXPECT_EQ(2, hash_table.find("world"));
    EXPECT_EQ(1, hash_table.find("a"));
    EXPECT_EQ(1, hash_table.find("b"));
    EXPECT_EQ(1, hash_table.find("c"));
    EXPECT_EQ(1, hash_table.find("d"));
    EXPECT_EQ(0, hash_table.find("e"));
}

TEST_F(HashTestFixture, TestDelete) {
    hash_table.del("hello");

    EXPECT_EQ(0, hash_table.find("hello"));
    EXPECT_EQ(2, hash_table.find("world"));
    EXPECT_EQ(1, hash_table.find("a"));
    EXPECT_EQ(1, hash_table.find("b"));
    EXPECT_EQ(1, hash_table.find("c"));
    EXPECT_EQ(1, hash_table.find("d"));
}

TEST(TestHash, TestEmptyHash) {
    Hash hash_table(2);
    EXPECT_EQ(0, hash_table.find("hello"));
    EXPECT_EQ(0, hash_table.find("world"));
}

TEST(TestHash, TestIncrease) {
    Hash hash_table(2);
    hash_table.increase("hello");
    hash_table.increase("world");
    hash_table.increase("hello");
    hash_table.increase("world");

    EXPECT_EQ(2, hash_table.find("hello"));
    EXPECT_EQ(2, hash_table.find("world"));
    EXPECT_EQ(0, hash_table.find("helloworld"));
}

TEST_F(LargeHashTestFixture, TestHist) {
    std::map<int, int> hist = hash_table.hist();

    int unique_word_count = 0;
    int list_count = 0;
    for (auto [len, count]: hist) {
        unique_word_count += len * count;
        list_count += count;
    }
    
    EXPECT_EQ(6, unique_word_count);
    EXPECT_EQ(10, list_count);
}

TEST(TestHash, TestHistEmpty) {
    Hash hash_table(100);
    std::map<int, int> hist = hash_table.hist();

    ASSERT_EQ(1, hist.size());
    EXPECT_EQ(100, hist[0]);
}

TEST_F(HashTestFixture, TestListAllKeys) {
    std::vector<std::string> keys = hash_table.list_all_keys();

    ASSERT_EQ(6, keys.size());
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "hello") != keys.end());
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "world") != keys.end());
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "a") != keys.end());
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "b") != keys.end());
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "c") != keys.end());
    EXPECT_TRUE(std::find(keys.begin(), keys.end(), "d") != keys.end());

    EXPECT_FALSE(std::find(keys.begin(), keys.end(), "e") != keys.end());
}

TEST(TestHash, TestListAllKeysEmpty) {
    Hash hash_table(3);
    std::vector<std::string> keys = hash_table.list_all_keys();

    ASSERT_EQ(0, keys.size());
}

TEST_F(HashTestFixture, TestList) {
    using namespace std::string_literals;

    std::vector<std::pair<std::string, int>> list = hash_table.list();

    ASSERT_EQ(6, list.size());
    EXPECT_TRUE(std::find(list.begin(), list.end(), std::make_pair("hello"s, 2)) != list.end());
    EXPECT_TRUE(std::find(list.begin(), list.end(), std::make_pair("world"s, 2)) != list.end());
    EXPECT_TRUE(std::find(list.begin(), list.end(), std::make_pair("a"s, 1)) != list.end());
    EXPECT_TRUE(std::find(list.begin(), list.end(), std::make_pair("b"s, 1)) != list.end());
    EXPECT_TRUE(std::find(list.begin(), list.end(), std::make_pair("c"s, 1)) != list.end());
    EXPECT_TRUE(std::find(list.begin(), list.end(), std::make_pair("d"s, 1)) != list.end());

    EXPECT_FALSE(std::find(list.begin(), list.end(), std::make_pair("e"s, 1)) != list.end());
}

TEST(TestHash, TestListEmpty) {
    Hash hash_table(3);
    std::vector<std::pair<std::string, int>> list = hash_table.list();

    ASSERT_EQ(0, list.size());
}
