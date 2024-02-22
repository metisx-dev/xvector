cmake_minimum_required(VERSION 3.11)

include(UseJava)

find_package(JNI REQUIRED)

#include_directories(${JNI_INCLUDE_DIRS})

get_target_property(xvector_JAR_FILE xvector-java JAR_FILE)
get_filename_component(xvector_JAR_DIR ${xvector_JAR_FILE} DIRECTORY)

macro(add_xvector_jni name lib src1)
  add_library(${name} SHARED ${src1} ${ARGN})

  add_dependencies(${name} xvector-jni-gen-headers)

  target_link_libraries(${name} PUBLIC ${lib})

  target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wundef)

  #message(STATUS "JAVA_HOME: $ENV{JAVA_HOME}")
  #message(STATUS "JNI_INCLUDE_DIRS: ${JNI_INCLUDE_DIRS}")

  target_include_directories(${name} PRIVATE
    ${JNI_INCLUDE_DIRS}
    )
  
  #set_target_properties(${name} PROPERTIES PREFIX "")
  set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${xvector_JAR_DIR}")
endmacro()

set(XVECTOR_JNI_NATIVE_SOURCES
  com_metisx_xvector_Buffer.cpp
  com_metisx_xvector_Context.cpp
  com_metisx_xvector_Filter.cpp
  com_metisx_xvector_IndexArray.cpp
  com_metisx_xvector_KnnQuery.cpp
  com_metisx_xvector_KnnResult.cpp
  com_metisx_xvector_Query.cpp
  com_metisx_xvector_VectorArray.cpp
  throw_exception.cpp
)

add_xvector_jni(xvector-jni-sim xvector-sim ${XVECTOR_JNI_NATIVE_SOURCES})
add_xvector_jni(xvector-jni xvector ${XVECTOR_JNI_NATIVE_SOURCES})
