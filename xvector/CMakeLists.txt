cmake_minimum_required(VERSION 3.11) 


list(APPEND XVECTOR_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

# metisx

add_library(metisx STATIC IMPORTED GLOBAL)

#list(APPEND METISX_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/metisx")

set_target_properties(metisx PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libmetisx.so
  #INTERFACE_INCLUDE_DIRECTORIES "${METISX_INCLUDE_DIRECTORIES}"
)

target_link_options(metisx INTERFACE
  -Wl,-rpath,${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# xvector-core

add_library(xvector-core STATIC IMPORTED GLOBAL)

set_target_properties(xvector-core PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libxvector-core.a
  INTERFACE_INCLUDE_DIRECTORIES "${XVECTOR_INCLUDE_DIRECTORIES}"
)

target_link_options(xvector-core INTERFACE
  -Wl,-rpath,${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# xvector

add_library(xvector STATIC IMPORTED GLOBAL)

set_target_properties(xvector PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libxvector.a
  INTERFACE_INCLUDE_DIRECTORIES "${XVECTOR_INCLUDE_DIRECTORIES}"
)

target_link_options(xvector INTERFACE
  -Wl,-rpath,${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_link_libraries(xvector INTERFACE xvector-core metisx)

add_library(xvector::xvector ALIAS xvector)

# xvector-sim

add_library(xvector-sim STATIC IMPORTED GLOBAL)

set_target_properties(xvector-sim PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libxvector-sim.a
  INTERFACE_INCLUDE_DIRECTORIES "${XVECTOR_INCLUDE_DIRECTORIES}"
)

target_link_options(xvector-sim INTERFACE
  -Wl,-rpath,${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_link_libraries(xvector-sim INTERFACE xvector-core)

add_library(xvector::xvector-sim ALIAS xvector-sim)