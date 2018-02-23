# cmake required
cmake_minimum_required(VERSION 3.8)

# project name and version
set(SHADOWSOCKS_NAME shadowsocks)
set(SHADOWSOCKS_VERSION 0.0.1)

# settup build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release FORCE)
endif ()

# cxx standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# cxx compile flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif ()

# include and sources dir
set(SHADOWSOCKS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SHADOWSOCKS_SOURCES_DIR ${CMAKE_SOURCE_DIR}/src/lib)

# common sources
aux_source_directory(${SHADOWSOCKS_SOURCES_DIR} SHADOWSOCKS_SOURCES)

# output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# platform macro
if (${WIN32})
    add_definitions(-D__windows__)
else ()
    add_definitions(-D__unix__)
endif ()

# sub target
add_subdirectory(${CMAKE_SOURCE_DIR}/src/client)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/server)
