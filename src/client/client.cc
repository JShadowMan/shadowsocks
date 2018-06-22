#include "shadowsocks/ss_core.h"
#include "shadowsocks/network/relay/ss_tcp_relay.h"


int main(int argc, char *argv[]) {
    SsCore::enableDebugLogger(SsLogger::LoggerLevel::LL_DEBUG);
    SsCore::initEnvironments();

    auto selector = std::make_shared<SsSelector>();
    auto tcpRelay = std::make_shared<SsTcpRelay>();

    return 0;
}
