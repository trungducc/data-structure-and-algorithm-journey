# Set the project name
project (priority_queue)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(priority_queue_test test/priority_queue_test.cc)
target_link_libraries(priority_queue_test 
    priority_queue
    utils
    gtest_main
)
add_test(NAME priority_queue_test COMMAND priority_queue_test)
