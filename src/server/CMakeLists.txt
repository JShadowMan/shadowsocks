# shadowsocks server
set(SHADOWSOCKS_CURRENT_MODULE ss-server)

# include dirs
include_directories(${SHADOWSOCKS_INCLUDE_DIR})

# add macro to cxx
add_definitions(-DSHADOWSOCKS_SERVER_MODULE)

# shadowsocks-server src
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SHADOWSOCKS_SERVER_SOURCES)

# build target
add_executable(
    ${SHADOWSOCKS_CURRENT_MODULE}
        ${SHADOWSOCKS_SOURCES}
        ${SHADOWSOCKS_INCLUDE_DIR}
        ${SHADOWSOCKS_SERVER_SOURCES}
)
