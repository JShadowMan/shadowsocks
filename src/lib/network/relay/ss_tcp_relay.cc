#include "shadowsocks/network/relay/ss_tcp_relay.h"


// SsTcpRelay constructor
SsTcpRelay::SsTcpRelay() : _proxy(std::make_shared<SsTcpSession>()) {
}

// start proxy any requests
void SsTcpRelay::startProxy(NetworkHost host, NetworkPort port) {
    if (!_proxy->listen(host, port)) {
        SsLogger::emergency("cannot start proxy for relay = ?");
    }

    SsSelector::select(_proxy, {SsSelector::SelectorEvent::SE_READABLE});
    SsLogger::debug("SsTcpRelay ready to proxy tcp requests");
}
