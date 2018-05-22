#ifndef __SHADOWSOCKS_UDP_RELAY_INCLUDED__
#define __SHADOWSOCKS_UDP_RELAY_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/ss_udp_network.h"


/**
 * Class: SsUdpRelay
 *
 *
 */
class SsUdpRelay {
    public:
        void startProxy(NetworkHost host, NetworkPort port);

    private:
        SsUdpNetwork _proxy;
};



#endif // __SHADOWSOCKS_UDP_RELAY_INCLUDED__
