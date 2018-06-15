#include "shadowsocks/network/ss_tcp_network.h"


// SsTcpNetwork constructor
SsTcpNetwork::SsTcpNetwork(SsNetwork::NetworkFamily family) :
    SsNetwork(family, NetworkType::NT_TCP) {
}

// SsTcpNetwork constructor
SsTcpNetwork::SsTcpNetwork(SsNetwork::Descriptor descriptor,
                           SsNetwork::Address address) :
    SsNetwork(descriptor, address, NetworkType::NT_TCP) {
}

// accept new connecting
SsNetwork::ConnectingTuple SsTcpNetwork::accept() {
    return SsNetwork::accept();
}

// connecting to host:port via TCP
void SsTcpNetwork::doConnect(SsNetwork::HostName host,
                             SsNetwork::HostPort port) {
    SsNetwork::doConnect(host, port);
}

// listening to host:port via TCP
void SsTcpNetwork::doListen(SsNetwork::HostName host,
                            SsNetwork::HostPort port) {
    SsNetwork::doListen(host, port);
}
