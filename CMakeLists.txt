cmake_minimum_required(VERSION 3.14)
project(LAB_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fPIC")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(sequence_lib SHARED
    src/Bit.cpp
    src/BitSequence.cpp
    src/sequence_api.cpp
    doc/ImmutableListSequence.hpp
    include/ImmutableListSequenceBuilder.hpp
    include/ImmutableArraySequenceBuilder.hpp
)

enable_testing()
find_package(GTest REQUIRED)

function(add_test_with_sources TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE} ${ARGN})
    target_link_libraries(${TEST_NAME} GTest::gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_test_with_sources(test_DynamicArray tests/test_DynamicArray.cpp)
add_test_with_sources(test_LinkedList tests/test_LinkedList.cpp)
add_test_with_sources(test_MutableArraySequence tests/test_MutableArraySequence.cpp)
add_test_with_sources(test_ImmutableArraySequence tests/test_ImmutableArraySequence.cpp)
add_test_with_sources(test_MutableListSequence tests/test_MutableListSequence.cpp)
add_test_with_sources(test_ImmutableListSequence tests/test_ImmutableListSequence.cpp)
add_test_with_sources(test_BitSequence tests/test_BitSequence.cpp src/Bit.cpp src/BitSequence.cpp)

set_target_properties(sequence_lib PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})