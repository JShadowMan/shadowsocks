#ifndef __SHADOWSOCKS_NETWORK_INCLUDED__
#define __SHADOWSOCKS_NETWORK_INCLUDED__
#pragma once


// other shadowsocks headers
#include "shadowsocks/ss_types.h"
#include "shadowsocks/ss_selector.h"


/* `Ss_Network` class */
class Ss_Network {
    public:
        enum class NetworkFamily:int8_t {
            NF_INET_4 = AF_INET,
            NF_INET_6 = AF_INET6
        };

        enum class NetworkType:int8_t {
            NT_TCP = SOCK_STREAM,
            NT_UDP = SOCK_DGRAM,
            NT_RAW = SOCK_RAW
        };

    public:
        Ss_Network(NetworkFamily family, NetworkType type);
        ~Ss_Network();

    public:
        static Ss_Network *generateTcpNetwork();
        static Ss_Network *generateUdpNetwork();

    public:
        bool listen(const char *host, int port);

    public:
        static void startSelect();
        static void stopSelect();

    private:
        bool createSocket();
        bool bindSocket(const char *host, int port);

        bool tcpSetSocketOpts();
        bool udpSetSocketOpts();
        bool toggleNonBlocking();

        bool tcpStartListening();
        bool udpStartListening();

    private:
        static sockaddr_storage socketGetAddr(const char *host, int port);
        static void acceptNewSocket(SOCKET s);
        static void socketEnvironmentInit();
        static void socketEnvironmentClean();
        static void registerInputToSelector();


    private:
        using NetworkSocket = SOCKET;

    private:
        NetworkFamily _family;
        NetworkType _type;
        NetworkSocket _socket;

        int _listenSize = 8;

    private:
        static bool _socketSetup;
        static bool _selectState;
        static int _availableNetworkCount;
        static std::list<SOCKET> _serverSockets;
        static std::shared_ptr<Ss_Selector> _selector;

    SELECTOR_CALLBACK:
        SELECTOR_CALLBACK_FUNCTION void selectorCallback(
            SOCKET s, Ss_Selector::SelectorEvent event);
};


#endif // __SHADOWSOCKS_NETWORK_INCLUDED__
