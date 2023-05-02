project(AliceHash)

add_library(Hash STATIC hash.cpp)
target_include_directories(Hash PUBLIC ../../include/cs5800)
