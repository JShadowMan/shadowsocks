#include "shadowsocks/network/ss_udp_network.h"
#include "shadowsocks/ss_logger.h"


// SsUdpNetwork constructor
SsUdpNetwork::SsUdpNetwork(SsNetwork::NetworkFamily family) :
    SsNetwork(family, NetworkType::NT_UDP) {
}

// SsUdpNetwork constructor
SsUdpNetwork::SsUdpNetwork(SsNetwork::Descriptor descriptor,
                           SsNetwork::Address address) :
    SsNetwork(descriptor, address, NetworkType::NT_UDP) {
}

// udp server unsupported accept connection
SsNetwork::ConnectingTuple SsUdpNetwork::accept() {
    return {INVALID_DESCRIPTOR, nullptr};
}

// UDP network unsupported connect action
void SsUdpNetwork::doConnect(SsNetwork::HostName host,
                             SsNetwork::HostPort port) {
    SsLogger::warning("UDP network unsupported connect operator");
}

// listening on host:port via UDP
void SsUdpNetwork::doListen(SsNetwork::HostName host,
                            SsNetwork::HostPort port) {
    SsNetwork::doListen(host, port);
}
