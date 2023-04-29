project(RBTree)

add_library(RBTree STATIC rbtree.cpp rbtree.hpp)

add_executable(RBMain rbtreeapp.cpp)
target_link_libraries(RBMain PUBLIC RBTree)

add_executable(TestRBTree rbtreesimpletest.cpp)
target_link_libraries(TestRBTree PUBLIC RBTree gtest_main gmock_main)
