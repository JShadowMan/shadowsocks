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
