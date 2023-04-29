cmake_minimum_required(VERSION 3.14)

project(CS5800Algorithms)

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(gtest)

add_subdirectory(src/hash)
add_subdirectory(src/rbtree)