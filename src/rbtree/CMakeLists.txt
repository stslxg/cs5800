project(RBTree)

add_library(RBTree STATIC rbtree.cpp rbtree.hpp)

add_executable(RBMain rbtreeapp.cpp)
target_link_libraries(RBMain RBTree)

add_executable(RBTest rbtreetest.cpp)
target_link_libraries(RBTest RBTree gtest_main gmock_main)
