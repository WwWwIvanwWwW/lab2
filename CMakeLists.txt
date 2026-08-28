cmake_minimum_required(VERSION 3.14)
project(LAB_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/Array)
include_directories(${CMAKE_SOURCE_DIR}/include/List)
include_directories(${CMAKE_SOURCE_DIR}/include/LazySequence)
include_directories(${CMAKE_SOURCE_DIR}/include/Stream)

add_library(sequence_lib SHARED
    src/Bit.cpp
    src/BitSequence.cpp
    src/sequence_api.cpp
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
add_test_with_sources(test_Vector tests/test_Vector.cpp)
add_test_with_sources(test_LazySequence tests/test_LazySequence.cpp)
add_test_with_sources(test_Generator tests/test_Generator.cpp)
add_test_with_sources(test_Cardinal tests/test_Cardinal.cpp)
add_test_with_sources(test_ReadOnlyStream tests/test_ReadOnlyStream.cpp)
add_test_with_sources(test_WriteOnlyStream tests/test_ReadOnlyStream.cpp)
add_test_with_sources(test_StatisticsCollector tests/test_StatisticsCollector.cpp)