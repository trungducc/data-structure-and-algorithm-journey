# Set the project name
project (queue_array)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(queue_array_test test/queue_array_test.cc)
target_link_libraries(queue_array_test 
    queue_array
    utils
    gtest_main
)
add_test(NAME queue_array_test COMMAND queue_array_test)
