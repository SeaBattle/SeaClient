 
cmake_minimum_required(VERSION 2.8)

project (sea_client)
 
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src) 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
 
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

include(CTest)
enable_testing()
         
set(CMAKE_C_FLAGS "-std=c99")

set (LIB_SOURCE
${PROJECT_SOURCE_DIR}/net.c
${PROJECT_SOURCE_DIR}/auth.c)
              
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories (/usr/include)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCE})