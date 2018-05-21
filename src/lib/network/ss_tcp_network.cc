#include "shadowsocks/network/ss_tcp_network.h"


// SsTcpNetwork constructor
SsTcpNetwork::SsTcpNetwork(SsNetwork::NetworkFamily family) :
    SsNetwork(family, NetworkType::NT_TCP) {
}

// do listen for tcp network
bool SsTcpNetwork::doListen(NetworkHost host, NetworkPort port) {
    return false;
}

// do connect for tcp network
bool SsTcpNetwork::doConnect(NetworkHost host, NetworkPort port) {
    return false;
}
