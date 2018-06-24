# Data Structure & Algorithm Journey

Data Structures & Algorithms implementations

## Requirements

 - [CMake v3.11+][1]
 - A C++ compiler (defaults to gcc)

## Building the tests

  Create a directory to contain the build outputs in the project root.

    mkdir build
    cd build

  Download googletest, configure and generate files with CMake.

    cmake ..

  Build executables and do all that linking stuff.

    make

  Run the tests

    make test

[1]: https://cmake.org
