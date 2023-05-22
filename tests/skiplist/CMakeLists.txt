project(skiplist)

add_executable(TestSkipList skiplist_simple_test.cpp skiplist_test_insert.cpp)
target_link_libraries(TestSkipList PUBLIC SkipList gtest_main gmock_main)
target_include_directories(TestSkipList PUBLIC ../../include/cs5800)
gtest_discover_tests(TestSkipList)
