#ifndef __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
#define __SHADOWSOCKS_TCP_NETWORK_INCLUDED__


#include "shadowsocks/network/ss_network.h"


class SsTcpNetwork : public SsNetwork {
    public:
        explicit SsTcpNetwork(NetworkFamily family);
        SsTcpNetwork(Descriptor descriptor, Address address);
        ConnectingTuple accept() final;

    protected:
        void doConnect(HostName host, HostPort port) final;
        void doListen(HostName host, HostPort port) final;
};


#endif // __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
