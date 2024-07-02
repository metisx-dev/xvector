cmake_minimum_required(VERSION 3.11)

project(xvector)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

set(CMAKE_CXX_STANDARD 20)
include(fetch-external)
set(CATCH2_ENABLE TRUE)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

# include(CTest)
# enable_testing()

set(XVECTOR_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/xvector)

add_subdirectory(xvector)

add_subdirectory(example)
add_subdirectory(java)
