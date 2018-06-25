cmake_minimum_required(VERSION 3.11)

add_definitions(-std=c++11)
add_definitions(-Werror) # stop compile on warning

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_DEBUG")

include_directories(
    "include/dynamic_array"
    "test")

set(SOURCE_FILES test/array_test.cc)
add_executable(dynamic_array ${SOURCE_FILES})
target_link_libraries(dynamic_array gtest_main)
add_test(NAME dynamic_array_test COMMAND dynamic_array)