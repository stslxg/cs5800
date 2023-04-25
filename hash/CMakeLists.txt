cmake_minimum_required(VERSION 3.13)

project(AliceHash)

add_library(Hash STATIC hash.cpp)

add_executable(Alice process_alice.cpp)
target_link_libraries(Alice Hash)
