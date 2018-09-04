# Set the project name
project (array)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(array_test test/array_test.cc)
target_link_libraries(array_test 
    array
    utils
    gtest_main
)
add_test(NAME array_test COMMAND array_test)
