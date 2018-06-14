cmake_minimum_required(VERSION 3.8)

# -- shadowsocks-client detail
set(SHADOWSOCKS_MODULE_NAME ss-cli)

# -- client sources
aux_source_directory(${SHADOWSOCKS_SOURCES}/client SHADOWSOCKS_MODULE_SOURCES)

# -- executable generated
add_executable(${SHADOWSOCKS_MODULE_NAME}
    ${SHADOWSOCKS_LIBRARIES_SOURCES} ${SHADOWSOCKS_MODULE_SOURCES})
