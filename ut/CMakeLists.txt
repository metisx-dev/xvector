project(xvector_test)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/xvector_test.cpp test_main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${local_include})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest dl xvector)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${ROOT_DIR}/build")