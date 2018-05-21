#include "shadowsocks/network/ss_udp_network.h"


// SsUdpNetwork constructor
SsUdpNetwork::SsUdpNetwork(SsNetwork::NetworkFamily family) :
    SsNetwork(family, NetworkType::NT_UDP) {
}

// do listen for udp network
bool SsUdpNetwork::doListen(NetworkHost host, NetworkPort port) {
    return false;
}

// do connect for udp network
bool SsUdpNetwork::doConnect(NetworkHost host, NetworkPort port) {
    return false;
}
