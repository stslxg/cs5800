project(RBTree)

add_library(RBTree STATIC rbtree.cpp)
target_include_directories(RBTree PUBLIC ../../include/cs5800)