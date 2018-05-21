#ifndef __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
#define __SHADOWSOCKS_TCP_NETWORK_INCLUDED__


/* shadowsocks headers */
#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/ss_network.h"


/**
 * Class: SsTcpNetwork
 *
 */
class SsTcpNetwork : SsNetwork {
    public:
        explicit SsTcpNetwork(NetworkFamily family = NetworkFamily::NF_INET_4);

    protected:
        bool doListen(NetworkHost host, NetworkPort port) final;
        bool doConnect(NetworkHost host, NetworkPort port) final;
};



#endif // __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
