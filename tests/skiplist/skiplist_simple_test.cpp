#include <gtest/gtest.h>
#include "skiplist/skiplist.hpp"

TEST(TestSkipListSimple, TestEmpty) {
    SkipList L;
    EXPECT_FALSE(L.lookup(0));
}

