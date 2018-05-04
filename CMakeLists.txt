# cmake required
cmake_minimum_required(VERSION 3.8)

# project name and version
set(SHADOWSOCKS_NAME shadowsocks)
set(SHADOWSOCKS_VERSION 0.0.1)

# cxx standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# cxx compile flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif ()

# platform setup
message(STATUS "Current platform: ${CMAKE_SYSTEM_NAME}")
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-D__linux__)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-D__windows__)
    link_libraries(ws2_32.lib)
ELSE ()
    message(ERROR "Other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

# add macro to cxx
add_definitions(-DSHADOWSOCKS_VERSION="${SHADOWSOCKS_VERSION}")

# include and sources dir
set(SHADOWSOCKS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SHADOWSOCKS_SOURCES_DIR ${CMAKE_SOURCE_DIR}/src/lib)

# sources for libraries
aux_source_directory(${SHADOWSOCKS_SOURCES_DIR} SHADOWSOCKS_SOURCES)

# output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# sub target
add_subdirectory(${CMAKE_SOURCE_DIR}/src/client)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/server)
