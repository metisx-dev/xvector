cmake_minimum_required(VERSION 3.11)

add_executable(xvec-unit-test
    xvector_test.cpp
    test_main.cpp)

target_link_libraries(xvec-unit-test PRIVATE gtest dl xvector)
