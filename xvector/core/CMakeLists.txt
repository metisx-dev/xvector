cmake_minimum_required(VERSION 3.11)

#set(XVEC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(src)
#add_subdirectory(ut)

add_library(xvector-core STATIC
    context_base.cpp
    device_buffer_base.cpp
    distance_result_base.cpp
    distance_query_base.cpp
    filter_base.cpp
    index_array_base.cpp
    knn_query_base.cpp
    knn_result_base.cpp
    object.cpp
    vector_array_base.cpp)

target_include_directories(xvector-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(xvector-core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(xvector-core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(xvector-core PRIVATE -Wall -Wextra -Wpedantic -Werror -Wundef)
endif()
