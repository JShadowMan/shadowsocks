#ifndef __SHADOWSOCKS_TCP_RELAY_INCLUDED__
#define __SHADOWSOCKS_TCP_RELAY_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/ss_tcp_network.h"


/**
 * Class: SsTcpRelay
 *
 *
 */
class SsTcpRelay {
    public:
        void startProxy(NetworkHost host, NetworkPort port);

    private:
        SsTcpNetwork _proxy;
};


#endif // __SHADOWSOCKS_TCP_RELAY_INCLUDED__
