#include <iostream>
#include "shadowsocks/ss_core.h"
#include "shadowsocks/server/ss_server.h"


/**
 * entry of shadowsocks-server
 */
int main(int argc, char *argv[]) {
    Ss_Core::printShadowSocksHeader(std::cout);

    Ss_Server server;
    server.createDaemon();

    return 0;
}
