#ifndef __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
#define __SHADOWSOCKS_TCP_NETWORK_INCLUDED__


/* shadowsocks headers */
#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/ss_network.h"


/**
 * Class: SsTcpNetwork
 *
 */
class SsTcpNetwork : public SsNetwork {
    public:
        explicit SsTcpNetwork(NetworkFamily family = NetworkFamily::NF_INET_4);

    public:
        void selectorCallback(SsSelector::SelectorEvent event) final;

    protected:
        bool doListen(NetworkHost host, NetworkPort port) final;
        bool doConnect(NetworkHost host, NetworkPort port) final;

    private:
        bool bind(NetworkHost host, NetworkPort port) const;
};


#endif // __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
