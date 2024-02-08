cmake_minimum_required(VERSION 3.11)

#set(XVEC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(src)
#add_subdirectory(ut)

#if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#    target_compile_options(xvec-example PRIVATE -Wall -Wextra -Wpedantic -Werror -Wundef)
#endif()

macro(add_xvec_test name src1)
    add_executable(xvec-test-${name} ${src1} ${ARGN})
    target_link_libraries(xvec-test-${name} xvector)
    add_test(NAME xvec-test-${name} COMMAND valgrind --error-exitcode=1 --leak-check=full ./xvec-test-${name})
endmacro()

add_xvec_test(context xvec_test_context.c)
add_xvec_test(vector-array xvec_test_vector_array.c)
