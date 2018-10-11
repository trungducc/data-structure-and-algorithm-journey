# Set the project name
project (hash_table)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(hash_table_test test/hash_table_test.cc)
target_link_libraries(hash_table_test 
    hash_table
    gtest_main
)
add_test(NAME hash_table_test COMMAND hash_table_test)
