cmake_minimum_required(VERSION 3.28)
project(LAB_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_subdirectory(src)

enable_testing()

add_executable(tests
    tests/test_DynamicArray.cpp
    tests/test_LinkedList.cpp
    tests/test_Sequence.cpp
)

find_package(GTest REQUIRED)

target_include_directories(tests PRIVATE include)

target_link_libraries(tests
    GTest::gtest
    GTest::gtest_main
    pthread
)

add_test(NAME DynamicArrayTests COMMAND tests)
add_test(NAME LinkedListTests COMMAND tests)
add_test(NAME SequenceTests COMMAND tests)