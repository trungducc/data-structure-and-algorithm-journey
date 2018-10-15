# Set the project name
project (binary_search)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(binary_search_test test/binary_search_test.cc)
target_link_libraries(binary_search_test 
    binary_search
    gtest_main
)
add_test(NAME binary_search_test COMMAND binary_search_test)
