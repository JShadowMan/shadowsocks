#include <iostream>
#include <cstdlib>
#include "shadowsocks/ss_core.h"
#include "shadowsocks/server/ss_server.h"


/**
 * entry of shadowsocks-server
 */
int main(int argc, char *argv[]) {
    Ss_Core::printShadowSocksHeader(std::cout);

    Ss_Server server;
    if (!server.startDaemon()) {
        Ss_Core::printLastError("cannot start daemon");
        std::exit(1);
    }

    if (!server.startListening()) {
        Ss_Core::printLastError("tcp/udp listening error occurs");
        std::exit(1);
    }

    int number;
    std::cin >> number;

    return 0;
}
