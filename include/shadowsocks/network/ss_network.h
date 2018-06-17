#ifndef __SHADOWSOCKS_NETWORK_INCLUDED__
#define __SHADOWSOCKS_NETWORK_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_selector.h"


class SsNetwork {
    public:
        enum class NetworkFamily : uint8_t {
            NF_INET_4 = AF_INET,
            NF_INET_6 = AF_INET6
        };
        enum class NetworkType : uint8_t {
            NT_RAW = SOCK_RAW,
            NT_TCP = SOCK_STREAM,
            NT_UDP = SOCK_DGRAM
        };
        using HostName = const char *;
        using HostPort = int;
        using Address = sockaddr_storage;
        using Descriptor = SsSelector::Descriptor;
        using ConnectingTuple = std::pair<Descriptor, std::shared_ptr<Address>>;

    protected:
        enum class NetworkState : uint8_t {
            NS_NONE = 0x0,
            NS_LISTEN = 0x1,
            NS_ESTABLISHED = 0x2
        };

    public:
        SsNetwork(NetworkFamily family, NetworkType type);
        SsNetwork(Descriptor descriptor, Address address, NetworkType type);
        ~SsNetwork();
        Descriptor getDescriptor() const;
        void connect(HostName host, HostPort port);
        void listen(HostName host, HostPort port);
        virtual ConnectingTuple accept();

    protected:
        virtual void doConnect(HostName host, HostPort port);
        virtual void doListen(HostName host, HostPort port);

    private:
        NetworkFamily _family;
        NetworkType _type;
        NetworkState _state = NetworkState::NS_NONE;
        Descriptor _descriptor;

    friend std::ostream &operator<<(std::ostream &o, SsNetwork *network);
    friend std::ostream &operator<<(std::ostream &o, NetworkFamily &family);
    friend std::ostream &operator<<(std::ostream &o, NetworkType &type);
    friend std::ostream &operator<<(std::ostream &o, NetworkState &state);
};


#endif // __SHADOWSOCKS_NETWORK_INCLUDED__
