cmake_minimum_required(VERSION 3.9)

# global variable
set(SHADOWSOCKS_NAME shadowsocks)

# project name
project(${SHADOWSOCKS_NAME})

# cpp standard
set(CMAKE_CXX_STANDARD 11)

# directories to include
include_directories(${CMAKE_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_SOURCE_DIR}/src SHADOWSOCKS_SOURCES)

# openssl libraries
link_libraries(crypto)

# cmake target
add_executable(${SHADOWSOCKS_NAME} ${SHADOWSOCKS_SOURCES} ${CMAKE_SOURCE_DIR}/include include/shadowsocks/ss_logger.h src/ss_logger.cc include/shadowsocks/ss_selector.h src/ss_selector.cc include/shadowsocks/ss_client.h src/ss_client.cc include/shadowsocks/ss_server.h include/shadowsocks/ss_service.h src/ss_service.cc include/shadowsocks/ss_daemon.h src/ss_daemon.cc src/ss_server.cc)
