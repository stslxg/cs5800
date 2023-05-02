project(RBTree)

add_executable(RBMain rbtreeapp.cpp)
target_link_libraries(RBMain PUBLIC RBTree)
target_include_directories(RBMain PUBLIC ../../include/cs5800)