cmake_minimum_required(VERSION 3.11)

include(CTest)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in lib/googletest/download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/lib/googletest/download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/lib/googletest/download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/lib/googletest/src"
                 "${CMAKE_BINARY_DIR}/lib/googletest/build")

# Link targets against gtest, gmock,
add_subdirectory(dynamic_array)
# add_subdirectory(singly_linked_list)