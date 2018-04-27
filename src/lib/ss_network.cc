#include <iostream>
#include <cstdlib>
#include <cstring>
#include "shadowsocks/ss_network.h"


// header include
#ifdef __linux__
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
#   include <netdb.h>
#   include <unistd.h>
#elif __windows__
#   include <ws2tcpip.h>
#endif


// utils for macro
#ifdef __linux__
#   define SOCKET_CLOSE(_S) close((_S))
#elif __windows__
#   define SOCKET_CLOSE(_S) closesocket((_S))
#endif


// static members initializing
#ifdef __windows__
// on windows
bool Ss_Network::_socketSetup = false;

#endif


// Ss_Network constructor
Ss_Network::Ss_Network(NetworkFamily family, NetworkType type)
    : _family(family), _type(type) {
}

// destructor: close network
Ss_Network::~Ss_Network() {
    SOCKET_CLOSE(_socket);
    std::cout << "close socket success, socket = " << _socket
              << std::endl;

#ifdef __windows__
    winSocketShutdown();
#endif
}

// tcp network factory
Ss_Network *Ss_Network::generateTcpMetwork() {
    return new Ss_Network(NetworkFamily::NF_INET_4, NetworkType::NT_TCP);
}

// udp network factory
Ss_Network *Ss_Network::generateUdpNetwork() {
    return new Ss_Network(NetworkFamily::NF_INET_4, NetworkType::NT_UDP);
}

// create listen socket
bool Ss_Network::listen(const char *host, int port) {
    if (!createSocket()) {
        std::cerr << "create socket error" << std::endl;
        std::exit(1);
    }

    if (!bindSocket(host, port)) {
        std::cerr << "bind socket error" << std::endl;
        std::exit(1);
    }

    return true;
}

// create socket and setup
bool Ss_Network::createSocket() {
#ifdef __windows__
    // socket initializing on windows platform
    winSocketSetup();
#endif

    _socket = socket(static_cast<int>(_family), static_cast<int>(_type), 0);
    if (static_cast<int>(_socket) < 0) {
        return false;
    }

    std::cout << "create socket success, socket = " << _socket
              << std::endl;

    return true;
}

// bind socket fd to `sockaddr`
bool Ss_Network::bindSocket(const char *host, int port) {
    sockaddr_storage socketAddr = socketGetAddr(host, port);
    auto bindAddr = (sockaddr*) &socketAddr;

    if (bind(_socket, bindAddr, sizeof(socketAddr)) == SOCKET_ERROR) {
        return false;
    }

    std::cout << "bind " << _socket << " to " << host << ":" << port
              << std::endl;

    return true;
}

// create `sockaddr_storage` by host and port
sockaddr_storage Ss_Network::socketGetAddr(const char *host, int port) {
    union {
        sockaddr_storage ss;
        sockaddr_in s4;
        sockaddr_in6 s6;
    } socketAddr = {0};
    std::memset(&socketAddr, 0, sizeof(socketAddr));

    hostent *he = gethostbyname(host);
    if (he == nullptr) {
        std::cerr << "cannot resolve " << host << std::endl;
        std::exit(1);
    }

    if (he->h_addrtype == static_cast<int>(NetworkFamily::NF_INET_4)) {
        socketAddr.s4.sin_family = he->h_addrtype;
        std::memcpy(&socketAddr.s4.sin_addr, he->h_addr_list[0],
                    static_cast<size_t>(he->h_length));
    } else if (he->h_addrtype == static_cast<int>(NetworkFamily::NF_INET_6)) {
        socketAddr.s6.sin6_family = he->h_addrtype;
        std::memcpy(&socketAddr.s6.sin6_addr, he->h_addr_list[0],
                    static_cast<size_t>(he->h_length));
    } else {
        std::cerr << "undefined socket addr type for " << he->h_addrtype
                  << std::endl;
    }

    socketAddr.s4.sin_port = htons(static_cast<unsigned short>(port));
    return socketAddr.ss;
}

// methods for windows platform
#ifdef __windows__

// on windows socket setup
void Ss_Network::winSocketSetup() {
    if (!_socketSetup) {
        WSADATA winSockEnv = {0};
        if (WSAStartup(MAKEWORD(2, 2), &winSockEnv) != 0) {
            std::cerr << "socket setup failure on windows" << std::endl;
            std::exit(1);
        }
        _socketSetup = true;
    }
}

// on windows socket shutdown
void Ss_Network::winSocketShutdown() {
    if (_socketSetup) {
        if (WSACleanup() != 0) {
            std::cerr << "socket shutdown failure on windows" << std::endl;
        }

        _socketSetup = false;

        std::cout << "socket shutdown success on windows" << std::endl;
    }
}

#endif
