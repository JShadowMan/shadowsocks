cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# -- application detail
set(APPLICATION_NAME shadowsocks)
project(${APPLICATION_NAME} CXX C)

# -- application version
set(SHADOWSOCKS_VERSION_MAJOR 0)
set(SHADOWSOCKS_VERSION_MINOR 0)
set(SHADOWSOCKS_VERSION_PATCH 1)
set(SHADOWSOCKS_VERSION "${SHADOWSOCKS_VERSION_MAJOR}.${SHADOWSOCKS_VERSION_MINOR}.${SHADOWSOCKS_VERSION_PATCH}")

# -- compiler features
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -- cmake build directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# -- build variables set within the cmake tree
include(cmake/BuildVariables.cmake)

# -- feature check for platform/compiler
include(cmake/FeatureCheck.cmake)

# -- set default build type
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build type not set - defaulting to Release")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build from: Debug Release RelWithDebInfo MinSizeRel Coverage." FORCE)
endif()

# -- compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

set(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} -O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -O0")

# -- build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(__type_debug__ YES)
else()
    set(__type_release__ YES)
endif()

# -- platform
message(STATUS "Current Platform: ${CMAKE_SYSTEM}")
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(__platform_linux__ YES)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(__platform_windows__ YES)
    link_libraries(ws2_32.lib)
endif()

# -- include/source root
set(SHADOWSOCKS_INCLUDE "${CMAKE_SOURCE_DIR}/include")
set(SHADOWSOCKS_SOURCES  "${CMAKE_SOURCE_DIR}/src")

# -- ss_config.h by auto generate
set(SHADOWSOCKS_CONFIG_INCLUDE  "${CMAKE_BINARY_DIR}/include")
configure_file(
    "${SHADOWSOCKS_INCLUDE}/config.h.in"
    "${SHADOWSOCKS_CONFIG_INCLUDE}/ss_config.h"
)

# -- set include directories
include_directories(${SHADOWSOCKS_INCLUDE} ${SHADOWSOCKS_CONFIG_INCLUDE})

# -- auto search source files
file(GLOB_RECURSE SHADOWSOCKS_LIBRARIES_SOURCES "${SHADOWSOCKS_SOURCES}/lib/*.cc")
#aux_source_directory(${SHADOWSOCKS_SOURCES}/lib SHADOWSOCKS_LIBRARIES_SOURCES)

# -- binaries target
add_subdirectory(${SHADOWSOCKS_SOURCES}/client)
add_subdirectory(${SHADOWSOCKS_SOURCES}/server)
