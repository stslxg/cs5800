project(RBTree)

add_library(RBTree STATIC rbtree.cpp rbtree.hpp)

add_executable(RBMain rbtreeapp.cpp)
target_link_libraries(RBMain PUBLIC RBTree)

add_executable(TestRBTree rbtree_simple_test.cpp rbtree_test_insert_fixup.cpp)
target_link_libraries(TestRBTree PUBLIC RBTree gtest_main gmock_main)
