#include "shadowsocks/network/ss_udp_network.h"


// SsUdpNetwork constructor
SsUdpNetwork::SsUdpNetwork(SsNetwork::NetworkFamily family) :
    SsNetwork(family, NetworkType::NT_UDP) {
}

// do listen for udp network
bool SsUdpNetwork::doListen(NetworkHost host, NetworkPort port) {
    if (!bind(host, port)) {
        SsLogger::emergency("bind socket = %d to %s:%d error",
                            getSocket(), host, port);
    }

    SsLogger::debug("socket = %d listening to %s:%d", getSocket(), host, port);
    return true;
}

// do connect for udp network
bool SsUdpNetwork::doConnect(NetworkHost host, NetworkPort port) {
    return false;
}

// bind udp socket to a addr
bool SsUdpNetwork::bind(NetworkHost host, NetworkPort port) {
    sockaddr_storage addr = socketAddr(host, port);
    auto bindAddr = (sockaddr*) &addr;

    if (!setSocketOpts()) {
        SsLogger::warning("change socket = %d opts error", getSocket());
    }

    if (!setNonBlocking()) {
        SsLogger::warning("enable non-blocking socket %d error", getSocket());
    }

    SsLogger::debug("udp socket = %d bind to %s:%d", getSocket(), host, port);
    return ::bind(getSocket(), bindAddr, sizeof(addr)) != SOCKET_ERROR;
}
