# Set the project name
project (graph)

# Add interface library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(graph_test
    test/directed_graph_test.cc
    test/undirected_graph_test.cc
)
target_link_libraries(graph_test 
    graph
    utils
    gtest_main
)
add_test(NAME graph_test COMMAND graph_test)

