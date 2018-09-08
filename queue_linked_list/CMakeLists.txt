# Set the project name
project (queue_linked_list)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(queue_linked_list_test test/queue_linked_list_test.cc)
target_link_libraries(queue_linked_list_test 
    queue_linked_list
    utils
    gtest_main
)
add_test(NAME queue_linked_list_test COMMAND queue_linked_list_test)
