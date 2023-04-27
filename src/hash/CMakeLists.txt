project(AliceHash)

add_library(Hash STATIC hash.cpp)

add_executable(Alice process_alice.cpp)
target_link_libraries(Alice Hash)

add_executable(TestHash hashtest.cpp hashtestwithmock.cpp)
target_link_libraries(TestHash Hash gtest_main gmock_main)

