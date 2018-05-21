#ifndef __SHADOWSOCKS_NETWORK_INCLUDED__
#define __SHADOWSOCKS_NETWORK_INCLUDED__

#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_core.h"


/**
 * Class: SsNetwork
 *
 *
 */
class SsNetwork {
    public:
        enum class NetworkFamily : uint8_t {
            NF_INET_4 = AF_INET,
            NF_INET_6 = AF_INET6
        };

        enum class NetworkType : uint8_t {
            NT_RAW = 0x00,
            NT_TCP = 0x01,
            NT_UDP = 0x02
        };

    private:
        enum class NetworkState : uint8_t {
            NS_NONE = 0x00,
            NS_LISTEN = 0x01,
            NS_CONNECT = 0x02
        };

    public:
        SsNetwork(NetworkFamily family, NetworkType type);

    public:
        bool listen(NetworkHost host, NetworkPort port);
        bool connect(NetworkHost host, NetworkPort port);

    protected:
        virtual bool doListen(NetworkHost host, NetworkPort port) = 0;
        virtual bool doConnect(NetworkHost host, NetworkPort port) = 0;

        static sockaddr_storage socketAddr(NetworkHost host, NetworkPort port);

    protected:
        inline SOCKET getSocket() const {
            return _socket;
        }

    private:
        void createSocket();

    private:
        SOCKET _socket;
        NetworkFamily _family;
        NetworkType _type;
        NetworkState _state;

    friend std::ostream &operator<<(std::ostream &out, NetworkState state);
};


/**
 * Exception: SocketCreateError
 *
 *
 */
//SHADOWSOCKS_EXCEPTION(SocketCreateError);



/**
 * Exception: SocketStateError
 *
 *
 */
//SHADOWSOCKS_EXCEPTION(SocketStateError);



/* utility methods */
std::ostream &operator<<(std::ostream &out, SsNetwork::NetworkFamily family);
std::ostream &operator<<(std::ostream &out, SsNetwork::NetworkType type);


#endif // __SHADOWSOCKS_NETWORK_INCLUDED__
