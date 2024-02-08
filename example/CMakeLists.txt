cmake_minimum_required(VERSION 3.11)

#set(XVEC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(src)
#add_subdirectory(ut)

#if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#    target_compile_options(xvec-example PRIVATE -Wall -Wextra -Wpedantic -Werror -Wundef)
#endif()

macro(add_xvec_example name src1)
    add_executable(${name} ${src1} ${ARGN})
    target_link_libraries(${name} xvector)
    add_test(NAME ${name} COMMAND valgrind -s --error-exitcode=1 --leak-check=full ./${name})
endmacro()

add_xvec_example(example example.c helper.cpp)

add_custom_command(
    TARGET example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resources
    COMMENT "Creating symlink to source directory in the binary directory"
)
