project(RBTree)

add_library(RBTree STATIC rbtree.cpp rbtree.hpp)

add_executable(RBMain rbtreeapp.cpp)
target_link_libraries(RBMain RBTree)

add_executable(TestRBTree rbtreesimpletest.cpp)
target_link_libraries(TestRBTree RBTree gtest_main gmock_main)
