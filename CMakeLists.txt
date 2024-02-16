cmake_minimum_required(VERSION 3.11)

project(xvector)

option(XVECTOR_BUILD_SIM "Build xvector with simulation" ON)
option(XVECTOR_BUILD_CORE_ONLY "Build xvector with core only" OFF)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

message("Building core only")
add_subdirectory(xvector)

if (NOT ${XVECTOR_BUILD_CORE_ONLY})
  add_subdirectory(test)
  add_subdirectory(example)
endif()
