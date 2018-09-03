# Set the project name
project (utils)

# Add interface library
add_library(${PROJECT_NAME} src/utils.cc)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)

# Add tests and link with libraries
add_executable(utils_test test/utils_test.cc)
target_link_libraries(utils_test
    utils
    gtest_main
)
add_test(NAME utils_test COMMAND utils_test)
