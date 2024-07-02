cmake_minimum_required(VERSION 3.11)

macro(add_xvec_example name lib src1)
  add_executable(${name} ${src1} ${ARGN}) 

  # if (${CATCH2_ENABLE})
    target_link_libraries(${name} PUBLIC ${lib} Catch2::Catch2WithMain)

  # else()
  #   target_link_libraries(${name} ${lib})
  #   add_test(NAME ${name}
  #     #COMMAND valgrind -s --error-exitcode=1 --leak-check=full ./${name}-${target}
  #     COMMAND ./${name}
  #     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  #   )
  # endif()
 
  set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  
  add_custom_command(
    TARGET ${name} POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${XVECTOR_HOME_DIRECTORY} ${CMAKE_CURRENT_BINARY_DIR}/xvector
    COMMENT "Creating symlink to source directory in the binary directory"
  )

endmacro()

#add_xvec_example(example-sim xvector-sim example.c helper.cpp)
#add_xvec_example(example xvector example.c helper.cpp)
add_xvec_example(example-catch2 xvector example_catch2.cpp helper.cpp)

