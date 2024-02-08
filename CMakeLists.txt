cmake_minimum_required(VERSION 3.11)

project(xvector)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_subdirectory(xvector)
add_subdirectory(test)
add_subdirectory(example)
