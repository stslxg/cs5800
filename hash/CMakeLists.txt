cmake_minimum_required(VERSION 3.14)

project(AliceHash)

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(gtest)

add_library(Hash STATIC hash.cpp)

add_executable(Alice process_alice.cpp)
target_link_libraries(Alice Hash)

add_executable(TestHash hashtest.cpp)
target_link_libraries(TestHash Hash gtest_main gmock_main)
