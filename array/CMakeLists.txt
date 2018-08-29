cmake_minimum_required(VERSION 3.11)

include_directories(
    "include/array"
    "test"
)

# Add interface library
add_library(array INTERFACE)
target_include_directories(array INTERFACE
    "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(array_test test/array_test.cc)
target_link_libraries(array_test 
    array
    gtest_main
)
add_test(NAME array_test COMMAND array_test)
