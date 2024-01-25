cmake_minimum_required(VERSION 3.11)

project(xvector)

set(CMAKE_CXX_STANDARD 17)
set(XVEC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(ut)