 
cmake_minimum_required(VERSION 2.8) 

project (seaclient_example)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
            
set(CMAKE_C_FLAGS "-std=c99") 
 
set (SOURCE  
	${PROJECT_SOURCE_DIR}/main.c
	${PROJECT_SOURCE_DIR}/user_actions.c
	) 
 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories(/usr/include)
include_directories(${CMAKE_SOURCE_DIR}/API/include)
include_directories(${CMAKE_SOURCE_DIR}/API/include/packet)
include_directories(${CMAKE_SOURCE_DIR}/API/include/packet/gen)
 
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries (${PROJECT_NAME} seaclient_api)