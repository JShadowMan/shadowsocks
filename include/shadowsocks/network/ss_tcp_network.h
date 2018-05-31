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
    protected:
        using Connection = std::pair<SOCKET, sockaddr_storage>;

    public:
        explicit SsTcpNetwork(NetworkFamily family = NetworkFamily::NF_INET_4);
        SsTcpNetwork(SOCKET fd, sockaddr_storage &ss);
        ~SsTcpNetwork() override = default;

    protected:
        bool doListen(NetworkHost host, NetworkPort port) final;
        bool doConnect(NetworkHost host, NetworkPort port) final;

        void readableHandler() override;
        void writableHandler() override;

        Connection acceptConnection();
        void receiveData();

    private:
        bool bind(NetworkHost host, NetworkPort port) const;
        bool receiveErrorDetect();
};


#endif // __SHADOWSOCKS_TCP_NETWORK_INCLUDED__
