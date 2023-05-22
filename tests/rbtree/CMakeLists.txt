project(RBTree)

add_executable(TestRBTree rbtree_simple_test.cpp rbtree_test_insert_fixup.cpp)
target_link_libraries(TestRBTree PUBLIC RBTree gtest_main gmock_main)
target_include_directories(TestRBTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include/cs5800)
gtest_discover_tests(TestRBTree)
