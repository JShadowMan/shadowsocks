# shadowsocks client
set(SHADOWSOCKS_MODULE ss-cli)

# include dir
include_directories(${SHADOWSOCKS_INCLUDE_DIR})

# add macro to cxx
add_definitions(-DSHADOWSOCKS_MODULE="Client")

# shadowsocks-server src
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SHADOWSOCKS_CLIENT_SOURCES)

# build target
add_executable(
    ${SHADOWSOCKS_MODULE}
        ${SHADOWSOCKS_SOURCES}
        ${SHADOWSOCKS_INCLUDE_DIR}
        ${SHADOWSOCKS_CLIENT_SOURCES}
)
