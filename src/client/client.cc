#include "shadowsocks/ss_core.h"
#include "shadowsocks/network/relay/ss_tcp_relay.h"


int main(int argc, char *argv[]) {
    SsCore::enableDebugLogger(SsLogger::LoggerLevel::LL_DEBUG);
    SsCore::initEnvironments();

    auto tcpRelay = new SsTcpRelay();

    return 0;
}
