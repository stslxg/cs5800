project(binomial-heap)

add_executable(BiHeapMain biheapREPL.cpp)
target_link_libraries(BiHeapMain BiHeap)
target_include_directories(BiHeapMain PUBLIC ../../include/cs5800)
