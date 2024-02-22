cmake_minimum_required(VERSION 3.11)

include(UseJava)

add_jar(XVectorExample
  SOURCES XVectorExample.java DataType.java NpyHeader.java Npy.java
  ENTRY_POINT XVectorExample
  INCLUDE_JARS xvector-java ${CMAKE_CURRENT_SOURCE_DIR}/gson-2.10.1.jar
  #OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/example
)

get_target_property(xvector_JAR_FILE xvector-java JAR_FILE)
get_filename_component(xvector_JAR_DIR ${xvector_JAR_FILE} DIRECTORY)
get_target_property(XVectorExample_JAR_FILE XVectorExample JAR_FILE)
get_filename_component(XVectorExample_JAR_DIR ${XVectorExample_JAR_FILE} DIRECTORY)

add_test(NAME XVectorExample
  COMMAND ${Java_JAVA_EXECUTABLE} -Djava.library.path=${xvector_JAR_DIR} -cp ${xvector_JAR_FILE}:${XVectorExample_JAR_FILE}:${XVectorExample_JAR_DIR}/gson-2.10.1.jar XVectorExample
  WORKING_DIRECTORY ${XVectorExample_JAR_DIR}
)

add_custom_command(
  TARGET XVectorExample POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/../../example ${XVectorExample_JAR_DIR}/resources
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${XVECTOR_HOME_DIRECTORY} ${CMAKE_CURRENT_BINARY_DIR}/xvector
  COMMENT "Creating symlink to source directory in the binary directory"
)

add_custom_command(TARGET XVectorExample POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_CURRENT_SOURCE_DIR}/gson-2.10.1.jar
                   ${XVectorExample_JAR_DIR}/gson-2.10.1.jar)
