add_library(xvec_buffer STATIC
    xvec_buffer_impl.cpp
)

target_include_directories(xvec_buffer PUBLIC ${XVEC_INCLUDE_DIR})

target_compile_options(xvec_buffer PRIVATE -fPIC)
