cmake_minimum_required(VERSION 3.11)

project(xvector)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

enable_testing()

set(XVECTOR_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/xvector)

add_subdirectory(xvector)

add_subdirectory(example)
add_subdirectory(java)
