#include "shadowsocks/network/ss_udp_network.h"


// SsUdpNetwork constructor
SsUdpNetwork::SsUdpNetwork(SsNetwork::NetworkFamily family) :
    SsNetwork(family, NetworkType::NT_UDP) {
}

// SsUdpNetwork constructor
SsUdpNetwork::SsUdpNetwork(SsNetwork::Descriptor descriptor,
                           SsNetwork::Address address) :
    SsNetwork(descriptor, address, NetworkType::NT_UDP) {
}
