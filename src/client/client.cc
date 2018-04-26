#include <iostream>
#include "shadowsocks/ss_core.h"
#include "shadowsocks/client/ss_client.h"


/**
 * entry of shadowsocks-client
 */
int main(int argc, char *argv[]) {
    Ss_Core::printShadowSocksHeader(std::cout);

    return 0;
}
