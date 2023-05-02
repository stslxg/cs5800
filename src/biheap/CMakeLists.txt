project(binomial-heap)

add_library(BiHeap STATIC biheap.cpp)
target_include_directories(BiHeap PUBLIC ../../include/cs5800)