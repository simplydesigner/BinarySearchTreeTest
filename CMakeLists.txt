
cmake_minimum_required(VERSION 2.8)

set(PROJECT BinarySearchTree)

project (${PROJECT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(TESTS_FOR_${PROJECT} "Include tests for project" ON)

set(HEADERS ${PROJECT_SOURCE_DIR}/test/BinarySearchTree.hpp)
set(SOURCES ${PROJECT_SOURCE_DIR}/test/BinarySearchTree.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/test)

add_library (${PROJECT} STATIC ${HEADERS} ${SOURCES})

if (TESTS_FOR_${PROJECT})
  add_subdirectory(test)
endif ()
