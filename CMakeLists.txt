cmake_minimum_required(VERSION 3.27)
project(mnist_reader)

# version number
set(CMAKE_CXX_STANDARD 20)

# copy file from current source directory to current binary directory
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/train-images.idx3-ubyte
        ${CMAKE_CURRENT_BINARY_DIR}/train-images.idx3-ubyte COPYONLY)

# executable
add_executable(mnist_reader main.cpp)
