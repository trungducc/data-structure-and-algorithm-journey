# Set the project name
project (binary_trees)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(binary_trees_test test/binary_tree_test.cc test/bstree_test.cc)
target_link_libraries(binary_trees_test 
    binary_trees
    gtest_main
)
add_test(NAME binary_trees_test COMMAND binary_trees_test)
