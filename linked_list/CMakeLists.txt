# Set the project name
project (linked_list)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(linked_list_test test/linked_list_test.cc)
target_link_libraries(linked_list_test 
    linked_list
    utils
    gtest_main
)
add_test(NAME linked_list_test COMMAND linked_list_test)

