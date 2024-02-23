cmake_minimum_required(VERSION 3.11)

find_package(Java REQUIRED)

message(STATUS "Java_JAVA_EXECUTABLE: ${Java_JAVA_EXECUTABLE}")
message(STATUS "Java_JAVAC_EXECUTABLE: ${Java_JAVAC_EXECUTABLE}")
message(STATUS "Java_JAVAH_EXECUTABLE: ${Java_JAVAH_EXECUTABLE}")
message(STATUS "Java_JAR_EXECUTABLE: ${Java_JAR_EXECUTABLE}")
message(STATUS "Java_VERSION_STRING: ${Java_VERSION_STRING}")
message(STATUS "Java_VERSION_MAJOR: ${Java_VERSION_MAJOR}")
message(STATUS "Java_VERSION_MINOR: ${Java_VERSION_MINOR}")
message(STATUS "Java_VERSION_PATCH: ${Java_VERSION_PATCH}")
message(STATUS "Java_VERSION_TWEAK: ${Java_VERSION_TWEAK}")
message(STATUS "Java_VERSION: ${Java_VERSION}")

include(UseJava)

set(XVECTOR_JAVA_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/Buffer.java
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/Context.java
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/Filter.java
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/IndexArray.java
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/KnnQuery.java
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/KnnResult.java
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/OpType.java
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/Query.java
  ${CMAKE_CURRENT_SOURCE_DIR}/com/metisx/xvector/VectorArray.java
)

add_jar(xvector-java
  SOURCES ${XVECTOR_JAVA_SRCS}
  OUTPUT_NAME xvector
  #OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

get_target_property(xvector_JAR_FILE xvector-java JAR_FILE)
get_filename_component(xvector_JAR_DIR ${xvector_JAR_FILE} DIRECTORY)
message(STATUS "xvector_JAR_FILE: ${xvector_JAR_FILE}")

set(XVECTOR_JNI_HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/native/com_metisx_xvector_Buffer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/native/com_metisx_xvector_Context.h
  ${CMAKE_CURRENT_SOURCE_DIR}/native/com_metisx_xvector_Filter.h
  ${CMAKE_CURRENT_SOURCE_DIR}/native/com_metisx_xvector_IndexArray.h
  ${CMAKE_CURRENT_SOURCE_DIR}/native/com_metisx_xvector_KnnQuery.h
  ${CMAKE_CURRENT_SOURCE_DIR}/native/com_metisx_xvector_KnnResult.h
  ${CMAKE_CURRENT_SOURCE_DIR}/native/com_metisx_xvector_Query.h
  ${CMAKE_CURRENT_SOURCE_DIR}/native/com_metisx_xvector_VectorArray.h
)

add_custom_command(
  OUTPUT ${XVECTOR_JNI_HEADER_FILES}
  COMMAND ${Java_JAVAC_EXECUTABLE} -d /tmp -h ${CMAKE_CURRENT_SOURCE_DIR}/native ${XVECTOR_JAVA_SRCS}
  DEPENDS ${xvector_JAR_FILE}
  COMMENT "CMake: Generating JNI header files..."  
)

add_custom_target(xvector-jni-gen-headers
  DEPENDS ${XVECTOR_JNI_HEADER_FILES}
)

#add_custom_target(xvector-jni-gen-headers ALL
#  DEPENDS xvector-java
#  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#  COMMENT "CMAKE: Generating JNI header files..."
#  COMMAND echo "Generating JNI header files..."
#  COMMAND ${Java_JAVAH_EXECUTABLE} -d ${CMAKE_CURRENT_SOURCE_DIR}/native -classpath ${xvector_JAR_FILE} com.metisx.xvector.Context
#)

add_subdirectory(native)
add_subdirectory(example)
