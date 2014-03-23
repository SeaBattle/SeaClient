 
cmake_minimum_required(VERSION 2.8) 

project (seaclient_api)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
            
set(CMAKE_C_FLAGS "-std=c99") 

set (API_SOURCE  
	${PROJECT_SOURCE_DIR}/net.c
	${PROJECT_SOURCE_DIR}/auth.c
	)
              
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}/packet")
include_directories (/usr/include)

add_library(${PROJECT_NAME} STATIC ${API_SOURCE})