#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rbtree.hpp"

TEST(TestRBTreeSimple, TestEmptyTree) {
    Tree tree;
    EXPECT_EQ(nullptr, tree.min());
    EXPECT_EQ(nullptr, tree.max());
    EXPECT_EQ(nullptr, tree.search(1));
    EXPECT_EQ(nullptr, tree.suc(nullptr));
    EXPECT_EQ(nullptr, tree.pred(nullptr));
    EXPECT_EQ(0, tree.get_depth());
}
