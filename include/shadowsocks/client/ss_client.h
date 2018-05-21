#ifndef __SHADOWSOCKS_CLIENT_INCLUDED__
#define __SHADOWSOCKS_CLIENT_INCLUDED__


/* shadowsocks headers */
#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/relay/ss_tcp_relay.h"
#include "shadowsocks/network/relay/ss_udp_relay.h"


/**
 * Class: SsClient
 *
 *
 */
class SsClient {
    public:
        SsClient(NetworkHost host, NetworkPort port);

    public:
        static bool hasDaemon();

    public:
        void start();

    private:
        SsTcpRelay _tcpRelay;
        SsUdpRelay _udpRelay;
};


#endif // __SHADOWSOCKS_CLIENT_INCLUDED__
