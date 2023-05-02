project(AliceHash)

add_executable(Alice process_alice.cpp)
target_link_libraries(Alice PUBLIC Hash)
target_include_directories(Alice PUBLIC ../../include/cs5800)