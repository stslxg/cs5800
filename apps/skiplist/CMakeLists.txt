project(skiplist)

add_executable(SkipListMain skiplistREPL.cpp)
target_link_libraries(SkipListMain PUBLIC SkipList)
target_include_directories(SkipListMain PUBLIC ../../include/cs5800)
