#include "shadowsocks/ss_core.h"
#include "shadowsocks/client/ss_client.h"


/**
 * entry of shadowsocks-client
 */
int main(int argc, char *argv[]) {
    SsCore::initShadowsocksEnvironments();
    SsCore::startDaemon();

    SsCore::atExit([] () {
        SsSelector::shutdownEventLoop();
        SsClient::shutdownProxyService();
    });

    SsClient::createClient("0.0.0.0", 9980);
    SsClient::startProxyService();

    return 0;
}
