 
cmake_minimum_required(VERSION 2.8) 

project (seaclient_api)

set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
            
set(CMAKE_C_FLAGS "-std=c99") 

set (API_SOURCE  
	${PROJECT_SOURCE_DIR}/net.c
	${PROJECT_SOURCE_DIR}/auth.c
	${PROJECT_SOURCE_DIR}/packet/auth_packet.c
	${PROJECT_SOURCE_DIR}/packet/service_packet.c
	${PROJECT_SOURCE_DIR}/packet/gen/ss_packet_header.pb-c.c
	${PROJECT_SOURCE_DIR}/packet/gen/ss_guest_auth.pb-c.c
	${PROJECT_SOURCE_DIR}/packet/gen/ss_error_packet.pb-c.c
	)

include_directories (${PROJECT_INCLUDE_DIR})
include_directories (${PROJECT_INCLUDE_DIR}/packet)
include_directories (${PROJECT_INCLUDE_DIR}/packet/gen)

add_library( protobuf-c SHARED IMPORTED )
set_target_properties( protobuf-c PROPERTIES IMPORTED_LOCATION /usr/local/lib/libprotobuf-c.so )

add_library(${PROJECT_NAME} STATIC ${API_SOURCE})
target_link_libraries (${PROJECT_NAME} protobuf-c)