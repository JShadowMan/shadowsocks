#include "shadowsocks/network/relay/ss_udp_relay.h"


// start proxy any request by UDP protocol
void SsUdpRelay::startProxy(NetworkHost host, NetworkPort port) {
    if (!_proxy.listen(host, port)) {
        SsLogger::emergency("cannot start proxy for relay = ?");
    }

    SsLogger::debug("SsUdpRelay ready to proxy udp requests");
}
