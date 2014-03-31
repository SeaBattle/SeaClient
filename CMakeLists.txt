 
cmake_minimum_required(VERSION 2.8)

project (whirlwind_root)
 
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
include_directories("${PROJECT_SOURCE_DIR}")
include_directories (/usr/include)

add_subdirectory(API)
add_subdirectory(ExampleClient)