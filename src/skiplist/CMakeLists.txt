project(skiplist)

add_library(SkipList STATIC skiplist.cpp)
target_include_directories(SkipList PUBLIC ../../include/cs5800)