cmake_minimum_required(VERSION 3.11)

#set(XVEC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(src)
#add_subdirectory(ut)

set(XVEC_SRCS
    detail/context_base.cpp
    detail/device_buffer_base.cpp
    detail/distance_result_base.cpp
    detail/distance_query_base.cpp
    detail/filter_base.cpp
    detail/index_array_base.cpp
    detail/knn_query_base.cpp
    detail/knn_result_base.cpp
    detail/object.cpp
    detail/vector_array_base.cpp
    sim/context.cpp
    sim/distance_query.cpp
    sim/distance_result.cpp
    sim/device_buffer.cpp
    sim/filter.cpp
    sim/index_array.cpp
    sim/knn_query.cpp
    sim/knn_result.cpp
    sim/query.cpp
    sim/vector_array.cpp
    sim/xvec_buffer.cpp
    sim/xvec_context.cpp
    sim/xvec_distance_query.cpp
    sim/xvec_distance_result.cpp
    sim/xvec_filter.cpp
    sim/xvec_index_array.cpp
    sim/xvec_knn_query.cpp
    sim/xvec_knn_result.cpp
    sim/xvec_query.cpp
    sim/xvec_vector_array.cpp
    )

add_library(xvector SHARED ${XVEC_SRCS})

target_include_directories(xvector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(xvector PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(xvector PRIVATE -Wall -Wextra -Wpedantic -Werror -Wundef)
endif()
