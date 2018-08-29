cmake_minimum_required(VERSION 3.11)

include_directories(
    "include/linked_list"
    "test"
)

# Add interface library
add_library(linked_list INTERFACE)
target_include_directories(linked_list INTERFACE
    "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(linked_list_test test/linked_list_test.cc)
target_link_libraries(linked_list_test 
    linked_list
    gtest_main
)
add_test(NAME linked_list_test COMMAND linked_list_test)