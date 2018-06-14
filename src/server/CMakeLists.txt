cmake_minimum_required(VERSION 3.8)

# -- shadowsocks-server detail
set(SHADOWSOCKS_MODULE_NAME ss-server)

# -- server sources
aux_source_directory(${SHADOWSOCKS_SOURCES}/server SHADOWSOCKS_MODULE_SOURCES)

# -- executable generated
add_executable(${SHADOWSOCKS_EXECUTEABLE}
        ${SHADOWSOCKS_MODULE_NAME} ${SHADOWSOCKS_MODULE_SOURCES})
