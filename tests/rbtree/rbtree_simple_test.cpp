#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rbtree/rbtree.hpp"

TEST(TestRBTreeSimple, TestEmptyTree) {
    Tree tree;
    EXPECT_EQ(nullptr, tree.min());
    EXPECT_EQ(nullptr, tree.max());
    EXPECT_EQ(nullptr, tree.search(1));
    EXPECT_EQ(nullptr, tree.suc(nullptr));
    EXPECT_EQ(nullptr, tree.pred(nullptr));
    EXPECT_EQ(0, tree.get_depth());
}

TEST(TestRBTreeSimple, TestInsertWithOneNode) {
    Tree tree;
    tree.insert(1);
    ASSERT_NE(nullptr, tree.min());
    ASSERT_NE(nullptr, tree.max());
    EXPECT_EQ(1, tree.min()->val);
    EXPECT_EQ(1, tree.max()->val);
    ASSERT_NE(nullptr, tree.search(1));
    EXPECT_EQ(1, tree.search(1)->val);
    EXPECT_EQ(nullptr, tree.search(1)->left);
    EXPECT_EQ(nullptr, tree.search(1)->right);
    EXPECT_EQ(nullptr, tree.pred(tree.search(1)));
    EXPECT_EQ(nullptr, tree.suc(tree.search(1)));
    EXPECT_EQ(1, tree.get_depth());
}

TEST(TestRBTreeSimple, TestInsertWithTwoNodes) {
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    ASSERT_NE(nullptr, tree.min());
    ASSERT_NE(nullptr, tree.max());
    EXPECT_EQ(1, tree.min()->val);
    EXPECT_EQ(2, tree.max()->val);
    ASSERT_NE(nullptr, tree.search(1));
    EXPECT_EQ(1, tree.search(1)->val);
    ASSERT_NE(nullptr, tree.search(2));
    EXPECT_EQ(2, tree.search(2)->val);
    EXPECT_EQ(nullptr, tree.suc(tree.max()));
    EXPECT_EQ(nullptr, tree.pred(tree.min()));
    EXPECT_EQ(tree.min(), tree.pred(tree.max()));
    EXPECT_EQ(tree.max(), tree.suc(tree.min()));
    EXPECT_EQ(2, tree.get_depth());
}

TEST(TestRBTreeSimple, TestInsertWithThreeNodes) {
    Tree tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    ASSERT_NE(nullptr, tree.min());
    ASSERT_NE(nullptr, tree.max());
    EXPECT_EQ(1, tree.min()->val);
    EXPECT_EQ(3, tree.max()->val);
    ASSERT_NE(nullptr, tree.search(1));
    EXPECT_EQ(1, tree.search(1)->val);
    ASSERT_NE(nullptr, tree.search(2));
    EXPECT_EQ(2, tree.search(2)->val);
    ASSERT_NE(nullptr, tree.search(3));
    EXPECT_EQ(3, tree.search(3)->val);
    EXPECT_EQ(tree.search(2), tree.pred(tree.search(3)));
    EXPECT_EQ(tree.search(2), tree.suc(tree.search(1)));
    EXPECT_EQ(tree.search(1), tree.pred(tree.search(2)));
    EXPECT_EQ(tree.search(3), tree.suc(tree.search(2)));
    EXPECT_EQ(2, tree.get_depth());
    EXPECT_EQ(tree.search(1), tree.search(2)->left);
    EXPECT_EQ(tree.search(3), tree.search(2)->right);
}


TEST(TestRBTreeSimple, TestDeleteWithOneNode) {
    Tree tree;
    tree.insert(1);
    tree.del(tree.search(1));
    EXPECT_EQ(nullptr, tree.min());
    EXPECT_EQ(nullptr, tree.max());
    EXPECT_EQ(nullptr, tree.search(1));
    EXPECT_EQ(0, tree.get_depth());
}

TEST(TestRBTreeSimple, TestDeleteWithTwoNodes) {
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    tree.del(tree.search(1));
    ASSERT_NE(nullptr, tree.min());
    ASSERT_NE(nullptr, tree.max());
    EXPECT_EQ(2, tree.min()->val);
    EXPECT_EQ(2, tree.max()->val);
    ASSERT_NE(nullptr, tree.search(2));
    EXPECT_EQ(2, tree.search(2)->val);
    EXPECT_EQ(nullptr, tree.search(1));
    EXPECT_EQ(nullptr, tree.pred(tree.search(2)));
    EXPECT_EQ(nullptr, tree.suc(tree.search(2)));
    EXPECT_EQ(1, tree.get_depth());
}

TEST(TestRBTreeSimple, TestDeleteWithThreeNodes) {
    Tree tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.del(tree.search(2));
    ASSERT_NE(nullptr, tree.min());
    ASSERT_NE(nullptr, tree.max());
    EXPECT_EQ(1, tree.min()->val);
    EXPECT_EQ(3, tree.max()->val);
    ASSERT_NE(nullptr, tree.search(1));
    EXPECT_EQ(1, tree.search(1)->val);
    ASSERT_NE(nullptr, tree.search(3));
    EXPECT_EQ(3, tree.search(3)->val);
    ASSERT_EQ(nullptr, tree.search(2));
}

TEST(TestRBTreeSimple, TestDeleteBothTwoNodes) {
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    tree.del(tree.search(1));
    tree.del(tree.search(2));
    EXPECT_EQ(nullptr, tree.min());
    EXPECT_EQ(nullptr, tree.max());
    EXPECT_EQ(nullptr, tree.search(1));
    EXPECT_EQ(nullptr, tree.search(2));
    EXPECT_EQ(0, tree.get_depth());
}
