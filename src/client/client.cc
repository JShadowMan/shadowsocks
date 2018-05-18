#include "shadowsocks/ss_core.h"
#include "shadowsocks/client/ss_client.h"


/**
 * entry of shadowsocks-client
 */
int main(int argc, char *argv[]) {
    SsCore::initShadowSocksEnvironments();

    auto client = new SsClient();

    return 0;
}
