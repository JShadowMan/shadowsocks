#include "shadowsocks/network/relay/ss_udp_relay.h"


// SsUdpRelay constructor
SsUdpRelay::SsUdpRelay(): _proxy(std::make_shared<SsUdpNetwork>()) {
}

// start proxy any request by UDP protocol
void SsUdpRelay::startProxy(NetworkHost host, NetworkPort port) {
    if (!_proxy->listen(host, port)) {
        SsLogger::emergency("cannot start proxy for relay = ?");
    }

    SsSelector::select(_proxy, {SsSelector::SelectorEvent::SE_READABLE});
    SsLogger::debug("SsUdpRelay ready to proxy udp requests");
}

