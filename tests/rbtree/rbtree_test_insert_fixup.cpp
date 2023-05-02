#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rbtree/rbtree.hpp"

class MockTree: public Tree {
public:
    MockTree(): Tree() {
        ON_CALL(*this, left_rotate(testing::_)).WillByDefault([this](Node *x) { Tree::left_rotate(x); });
        ON_CALL(*this, right_rotate(testing::_)).WillByDefault([this](Node *y) { Tree::right_rotate(y); });
    };
    MOCK_METHOD(void, left_rotate, (Node *x), (override));
    MOCK_METHOD(void, right_rotate, (Node *y), (override));
};

TEST(TestRBInsertFixup, TestCase3RightRotation) {
    MockTree tree;
    EXPECT_CALL(tree, right_rotate(testing::_)).Times(1);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
}

TEST(TestRBInsertFixup, TestCase3RightResult) {
    Tree tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    ASSERT_NE(nullptr, tree.search(2));
    ASSERT_NE(nullptr, tree.search(1));
    ASSERT_NE(nullptr, tree.search(3));

    EXPECT_EQ(false, tree.search(2)->red);
    EXPECT_EQ(true, tree.search(1)->red);
    EXPECT_EQ(true, tree.search(3)->red);

    EXPECT_EQ(tree.search(1), tree.search(2)->left);
    EXPECT_EQ(tree.search(3), tree.search(2)->right);
}

TEST(TestRBInsertFixup, TestCase3LeftRotation) {
    MockTree tree;
    EXPECT_CALL(tree, left_rotate(testing::_)).Times(1);
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
}

TEST(TestRBInsertFixup, TestCase3LeftResult) {
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    ASSERT_NE(nullptr, tree.search(2));
    ASSERT_NE(nullptr, tree.search(1));
    ASSERT_NE(nullptr, tree.search(3));

    EXPECT_EQ(false, tree.search(2)->red);
    EXPECT_EQ(true, tree.search(1)->red);
    EXPECT_EQ(true, tree.search(3)->red);

    EXPECT_EQ(tree.search(1), tree.search(2)->left);
    EXPECT_EQ(tree.search(3), tree.search(2)->right);
}

TEST(TestRBInsertFixup, TestCase2LeftRightRotation) {
    ::testing::InSequence s;

    MockTree tree;
    EXPECT_CALL(tree, left_rotate(testing::_)).Times(1);
    EXPECT_CALL(tree, right_rotate(testing::_)).Times(1);

    tree.insert(2);
    tree.insert(1);
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
}

TEST(TestRBInsertFixup, TestCase2LeftRightResult) {
    Tree tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);

    ASSERT_NE(nullptr, tree.search(2));
    ASSERT_NE(nullptr, tree.search(1));
    ASSERT_NE(nullptr, tree.search(5));
    ASSERT_NE(nullptr, tree.search(3));
    ASSERT_NE(nullptr, tree.search(4));

    EXPECT_EQ(false, tree.search(2)->red);
    EXPECT_EQ(false, tree.search(1)->red);
    EXPECT_EQ(false, tree.search(4)->red);
    EXPECT_EQ(true, tree.search(3)->red);
    EXPECT_EQ(true, tree.search(5)->red);

    EXPECT_EQ(tree.search(1), tree.search(2)->left);
    EXPECT_EQ(tree.search(4), tree.search(2)->right);
    EXPECT_EQ(tree.search(3), tree.search(4)->left);
    EXPECT_EQ(tree.search(5), tree.search(4)->right);
}

TEST(TestRBInsertFixup, TestCase2RightLeftRotation) {
    ::testing::InSequence s;

    MockTree tree;
    EXPECT_CALL(tree, right_rotate(testing::_)).Times(1);
    EXPECT_CALL(tree, left_rotate(testing::_)).Times(1);

    tree.insert(4);
    tree.insert(5);
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
}

TEST(TestRBInsertFixup, TestCase2RightLeftResult) {
    Tree tree;
    tree.insert(4);
    tree.insert(5);
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);

    ASSERT_NE(nullptr, tree.search(4));
    ASSERT_NE(nullptr, tree.search(5));
    ASSERT_NE(nullptr, tree.search(1));
    ASSERT_NE(nullptr, tree.search(3));
    ASSERT_NE(nullptr, tree.search(2));

    EXPECT_EQ(false, tree.search(4)->red);
    EXPECT_EQ(false, tree.search(5)->red);
    EXPECT_EQ(false, tree.search(2)->red);
    EXPECT_EQ(true, tree.search(1)->red);
    EXPECT_EQ(true, tree.search(3)->red);

    EXPECT_EQ(tree.search(2), tree.search(4)->left);
    EXPECT_EQ(tree.search(5), tree.search(4)->right);
    EXPECT_EQ(tree.search(1), tree.search(2)->left);
    EXPECT_EQ(tree.search(3), tree.search(2)->right);
}

TEST(TestRBInsertFixup, TestCase1RightLeftResult) {
    Tree tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(3);

    ASSERT_NE(nullptr, tree.search(2));
    ASSERT_NE(nullptr, tree.search(1));
    ASSERT_NE(nullptr, tree.search(4));
    ASSERT_NE(nullptr, tree.search(3));

    EXPECT_EQ(false, tree.search(2)->red);
    EXPECT_EQ(false, tree.search(1)->red);
    EXPECT_EQ(false, tree.search(4)->red);
    EXPECT_EQ(true, tree.search(3)->red);

    EXPECT_EQ(tree.search(1), tree.search(2)->left);
    EXPECT_EQ(tree.search(4), tree.search(2)->right);
    EXPECT_EQ(tree.search(3), tree.search(4)->left);
}

TEST(TestRBInsertFixup, TestCase1LeftRightResult) {
    Tree tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    tree.insert(2);

    ASSERT_NE(nullptr, tree.search(3));
    ASSERT_NE(nullptr, tree.search(1));
    ASSERT_NE(nullptr, tree.search(4));
    ASSERT_NE(nullptr, tree.search(2));

    EXPECT_EQ(false, tree.search(3)->red);
    EXPECT_EQ(false, tree.search(1)->red);
    EXPECT_EQ(false, tree.search(4)->red);
    EXPECT_EQ(true, tree.search(2)->red);

    EXPECT_EQ(tree.search(1), tree.search(3)->left);
    EXPECT_EQ(tree.search(4), tree.search(3)->right);
    EXPECT_EQ(tree.search(2), tree.search(1)->right);
}

TEST(TestRBInsertFixup, TestCase1LeftLeftResult) {
    Tree tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(1);

    ASSERT_NE(nullptr, tree.search(3));
    ASSERT_NE(nullptr, tree.search(2));
    ASSERT_NE(nullptr, tree.search(4));
    ASSERT_NE(nullptr, tree.search(1));

    EXPECT_EQ(false, tree.search(3)->red);
    EXPECT_EQ(false, tree.search(2)->red);
    EXPECT_EQ(false, tree.search(4)->red);
    EXPECT_EQ(true, tree.search(1)->red);

    EXPECT_EQ(tree.search(2), tree.search(3)->left);
    EXPECT_EQ(tree.search(4), tree.search(3)->right);
    EXPECT_EQ(tree.search(1), tree.search(2)->left);
}

TEST(TestRBInsertFixup, TestCase1RightRightResult) {
    Tree tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(4);

    ASSERT_NE(nullptr, tree.search(2));
    ASSERT_NE(nullptr, tree.search(1));
    ASSERT_NE(nullptr, tree.search(3));
    ASSERT_NE(nullptr, tree.search(4));

    EXPECT_EQ(false, tree.search(2)->red);
    EXPECT_EQ(false, tree.search(1)->red);
    EXPECT_EQ(false, tree.search(3)->red);
    EXPECT_EQ(true, tree.search(4)->red);

    EXPECT_EQ(tree.search(1), tree.search(2)->left);
    EXPECT_EQ(tree.search(3), tree.search(2)->right);
    EXPECT_EQ(tree.search(4), tree.search(3)->right);
}
