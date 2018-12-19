# Set the project name
project (sorting)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(sorting_test test/sorting_test.cc)
target_link_libraries(sorting_test 
    sorting
    gtest_main
)
add_test(NAME sorting_test COMMAND sorting_test)

