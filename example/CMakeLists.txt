cmake_minimum_required(VERSION 3.11)

macro(add_xvec_example name lib src1)
  add_executable(${name} ${src1} ${ARGN})

  target_link_libraries(${name} ${lib})

  set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  #get_target_property(OUTPUT_DIRECTORY ${name} RUNTIME_OUTPUT_DIRECTORY)
  #message(STATUS "---o> OUTPUT_DIRECTORY: ${OUTPUT_DIRECTORY}")

  add_custom_command(
    TARGET ${name} POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${XVECTOR_HOME_DIRECTORY} ${CMAKE_CURRENT_BINARY_DIR}/xvector
    COMMENT "Creating symlink to source directory in the binary directory"
  )

  add_test(NAME ${name}
    #COMMAND valgrind -s --error-exitcode=1 --leak-check=full ./${name}-${target}
    COMMAND ./${name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )

endmacro()

add_xvec_example(example-sim xvector-sim example.c helper.cpp)
add_xvec_example(example xvector example.c helper.cpp)
