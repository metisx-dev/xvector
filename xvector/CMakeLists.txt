cmake_minimum_required(VERSION 3.11)

#set(XVEC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(src)
#add_subdirectory(ut)

set(XVEC_SRCS
    detail/cpu/cpu_context.cpp
    detail/cpu/cpu_distance_query.cpp
    detail/cpu/cpu_distance_result.cpp
    detail/cpu/cpu_device_buffer.cpp
    detail/cpu/cpu_filter.cpp
    detail/cpu/cpu_index_array.cpp
    detail/cpu/cpu_knn_query.cpp
    detail/cpu/cpu_knn_result.cpp
    detail/cpu/cpu_query.cpp
    detail/cpu/cpu_vector_array.cpp
    xvec_buffer.cpp
    xvec_context.cpp
    xvec_distance_query.cpp
    xvec_distance_result.cpp
    xvec_filter.cpp
    xvec_index_array.cpp
    xvec_knn_query.cpp
    xvec_knn_result.cpp
    xvec_query.cpp
    xvec_vector_array.cpp
    )

add_library(xvector SHARED ${XVEC_SRCS})

target_include_directories(xvector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
#target_include_directories(xvector PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(xvector PRIVATE -Wall -Wextra -Wpedantic -Werror -Wundef)
endif()

#add_subdirectory(ut)
