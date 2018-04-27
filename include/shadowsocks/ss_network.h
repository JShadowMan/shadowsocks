#ifndef __SHADOWSOCKS_NETWORK_INCLUDED__
#define __SHADOWSOCKS_NETWORK_INCLUDED__


/* socket headers */
#ifdef __linux__
#   include <sys/types.h>
#   include <sys/socket.h>
#elif __windows__
#   include <Windows.h>
#   include <WinSock2.h>
#endif
#pragma once


// socket type definition
#ifdef __linux__
#   define SOCKET int
#elif __windows__
#   define SOCKET SOCKET
#endif


// socket error flag
#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif


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
        static Ss_Network *generateTcpMetwork();
        static Ss_Network *generateUdpNetwork();

    public:
        bool listen(const char *host, int port);

    private:
        bool createSocket();
        bool bindSocket(const char *host, int port);

    private:
        static sockaddr_storage socketGetAddr(const char *host, int port);

    private:
        using NetworkSocket = SOCKET;

    private:
        NetworkFamily _family;
        NetworkType _type;
        NetworkSocket _socket;

#ifdef __windows__
    private:
        static void winSocketSetup();
        static void winSocketShutdown();
        static bool _socketSetup;
#endif
};



#endif // __SHADOWSOCKS_NETWORK_INCLUDED__
