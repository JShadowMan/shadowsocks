#include "shadowsocks/network/relay/ss_tcp_relay.h"


// start proxy any requests
void SsTcpRelay::startProxy(NetworkHost host, NetworkPort port) {
    if (!_proxy.listen(host, port)) {
        SsLogger::emergency("cannot start proxy for relay = ?");
    }

    SsLogger::debug("SsTcpRelay ready to proxy tcp requests");
}
