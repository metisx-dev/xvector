add_subdirectory(xvec_buffer)

add_library(${PROJECT_NAME} SHARED xvector.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wextra -Wpedantic -fPIC)

target_include_directories(${PROJECT_NAME} PUBLIC ${XVEC_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    xvec_buffer
)
