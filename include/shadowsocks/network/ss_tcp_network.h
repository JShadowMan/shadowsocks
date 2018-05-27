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
        SsTcpNetwork(SOCKET fd, sockaddr_storage &ss);
        ~SsTcpNetwork() final = default;

    protected:
        bool doListen(NetworkHost host, NetworkPort port) final;
        bool doConnect(NetworkHost host, NetworkPort port) final;
        void readableHandler() final;
        void writableHandler() final;

    private:
        bool bind(NetworkHost host, NetworkPort port) const;
        void acceptNewConnection();
        void receiveDate();
        void receiveErrorDetect();
};


#endif // __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
