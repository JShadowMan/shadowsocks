# shadowsocks client
set(SHADOWSOCKS_MODULE ss-server)

# include dir
include_directories(${SHADOWSOCKS_INCLUDE_DIR})

# add macro to cxx
add_definitions(-DSHADOWSOCKS_MODULE="Server")
add_definitions(-D__shadowsocks_server__)

# shadowsocks-server src
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SHADOWSOCKS_SERVER_SOURCES)

# shadowsocks-server target
add_executable(
    ${SHADOWSOCKS_MODULE}
        ${SHADOWSOCKS_SOURCES}
        ${SHADOWSOCKS_INCLUDE_DIR}
        ${SHADOWSOCKS_SERVER_SOURCES}
)
