project(AliceHash)

add_executable(TestHash hashtest.cpp hashtestwithmock.cpp)
target_link_libraries(TestHash PUBLIC Hash gtest_main gmock_main)
target_include_directories(TestHash PUBLIC ../../include/cs5800)
gtest_discover_tests(TestHash)
