#include "shadowsocks/ss_core.h"
#include "shadowsocks/client/ss_client.h"


/**
 * entry of shadowsocks-client
 */
int main(int argc, char *argv[]) {
    SsCore::initShadowsocksEnvironments();
    SsCore::startDaemon();

    auto client = std::make_shared<SsClient>("0.0.0.0", 9980);
    if (!SsClient::hasDaemon()) {
        client->startEventLoop();
    }

    return 0;
}
