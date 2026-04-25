add_executable(LAB_2 main.cpp)

target_include_directories(LAB_2 PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(LAB_2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})