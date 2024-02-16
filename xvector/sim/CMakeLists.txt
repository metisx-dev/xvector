cmake_minimum_required(VERSION 3.11)

#set(XVEC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(src)
#add_subdirectory(ut)

add_library(xvector-sim STATIC 
    context.cpp
    distance_query.cpp
    distance_result.cpp
    device_buffer.cpp
    filter.cpp
    index_array.cpp
    knn_query.cpp
    knn_result.cpp
    query.cpp
    vector_array.cpp
    xvec_buffer.cpp
    xvec_context.cpp
    xvec_distance_query.cpp
    xvec_distance_result.cpp
    xvec_filter.cpp
    xvec_index_array.cpp
    xvec_knn_query.cpp
    xvec_knn_result.cpp
    xvec_query.cpp
    xvec_vector_array.cpp)

target_include_directories(xvector-sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(xvector-sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(xvector-sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(xvector-sim PUBLIC xvector-core)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(xvector-sim PRIVATE -Wall -Wextra -Wpedantic -Werror -Wundef)
endif()
