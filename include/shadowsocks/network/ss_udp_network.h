#ifndef __SHADOWSOCKS_UDP_NETWORK_INCLUDED__
#define __SHADOWSOCKS_UDP_NETWORK_INCLUDED__


#include "shadowsocks/network/ss_network.h"


class SsUdpNetwork : public SsNetwork {
    public:
        explicit SsUdpNetwork(NetworkFamily family);
        SsUdpNetwork(Descriptor descriptor, Address address);
};


#endif // __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
