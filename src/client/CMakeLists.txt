# shadowsocks client
set(SHADOWSOCKS_CURRENT_MODULE ss-cli)

# include dir
include_directories(${SHADOWSOCKS_INCLUDE_DIR})

# add macro to cxx
add_definitions(-DSHADOWSOCKS_CLIENT_MODULE)

# build target
add_executable(
    ${SHADOWSOCKS_CURRENT_MODULE}
        ${SHADOWSOCKS_SOURCES}
        ${SHADOWSOCKS_INCLUDE_DIR}
        shadowsocks-client.cc
)
