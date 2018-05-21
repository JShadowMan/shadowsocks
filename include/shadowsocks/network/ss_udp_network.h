#ifndef __SHADOWSOCKS_UDP_NETWORK_INCLUDED__
#define __SHADOWSOCKS_UDP_NETWORK_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/ss_network.h"


/**
 * Class: SsUdpNetwork
 *
 *
 */
class SsUdpNetwork : SsNetwork {
    public:
        explicit SsUdpNetwork(NetworkFamily family = NetworkFamily::NF_INET_4);

    protected:
        bool doListen(NetworkHost host, NetworkPort port) final;
        bool doConnect(NetworkHost host, NetworkPort port) final;
};




#endif // __SHADOWSOCKS_UDP_NETWORK_INCLUDED__
