#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_network.h"


// header include
#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#define SOCKET_CLOSE(_S)        close((_S))


#elif __windows__
#include <ws2tcpip.h>

#define SOCKET_CLOSE(_S)        closesocket((_S))


#endif /* header included */


// static members initializing
#ifdef __windows__
// on windows
bool Ss_Network::_socketSetup = false;


#endif


// common static members initializing
int Ss_Network::_availableNetworkCount = 0;


// Ss_Network constructor
Ss_Network::Ss_Network(NetworkFamily family, NetworkType type)
    : _family(family), _type(type), _selector(new Ss_Selector()) {
    _availableNetworkCount++;
}

// destructor: close network
Ss_Network::~Ss_Network() {
    SOCKET_CLOSE(_socket);
    std::cout << "close socket success, socket = " << _socket
              << std::endl;

    delete _selector;
    _availableNetworkCount--;

#ifdef __windows__
    winSocketShutdown();
#endif
}

// tcp network factory
Ss_Network *Ss_Network::generateTcpNetwork() {
    return new Ss_Network(NetworkFamily::NF_INET_4, NetworkType::NT_TCP);
}

// udp network factory
Ss_Network *Ss_Network::generateUdpNetwork() {
    return new Ss_Network(NetworkFamily::NF_INET_4, NetworkType::NT_UDP);
}

// create listen socket
bool Ss_Network::listen(const char *host, int port) {
    if (!createSocket()) {
        Ss_Core::printLastError("create socket error");
        std::exit(1);
    }

    if (!bindSocket(host, port)) {
        Ss_Core::printLastError("bind socket error");
        std::exit(1);
    }

    bool listenResult = _type == NetworkType::NT_TCP ? tcpStartListening()
        : udpStartListening();
    if (!listenResult) {
        std::stringstream ss;
        ss << "socket: " << _socket;
        Ss_Core::printLastError(ss.str().c_str());
        std::exit(1);
    }

    _selector->registerSocket(_socket, {
        Ss_Selector::SelectorEvent::SE_READABLE
    });

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

    bool result = (_type == NetworkType::NT_TCP)
                  ? tcpSetSocketOpts() : udpSetSocketOpts();
    if (!result) {
        Ss_Core::printLastError("cannot set socket options");
        std::exit(1);
    }

    if (!toggleNonBlocking()) {
        Ss_Core::printLastError("cannot set socket blocking state");
        std::exit(1);
    }

    if (bind(_socket, bindAddr, sizeof(socketAddr)) == SOCKET_ERROR) {
        return false;
    }

    std::cout << "bind " << _socket << " to " << host << ":" << port
              << std::endl;

    return true;
}

bool Ss_Network::udpSetSocketOpts() {
    return true;
}

// add sme options to tcp network socket
bool Ss_Network::tcpSetSocketOpts() {
    int openFlag = 1;
    int result;

    result = setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR,
                        (char *)&openFlag, sizeof(openFlag));
    return result == OPERATOR_SUCCESS;
}

// set non-blocking for socket
bool Ss_Network::toggleNonBlocking() {
#ifdef __linux__
    int flags = fcntl(_socket, F_GETFL, 0);
    if (fcntl(_socket, F_SETFL, flags | O_NONBLOCK) != OPERATOR_SUCCESS) {
        return false;
    }
#elif __windows__
    u_long openFlag = 1L;
    if (ioctlsocket(_socket, FIONBIO, &openFlag) != OPERATOR_SUCCESS) {
        return false;
    }
#endif

    std::cout << "set non-blocking for " << _socket << std::endl;

    return true;
}

// start listening for tcp network
bool Ss_Network::tcpStartListening() {
    if (::listen(_socket, _listenSize) == SOCKET_ERROR) {
        return false;
    }

    std::cout << "tcp socket " << _socket << " start listening" << std::endl;

    return true;
}

// start listening for udp network
bool Ss_Network::udpStartListening() {
    std::cout << "udp socket " << _socket << " start listening" << std::endl;

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
        std::stringstream ss;
        ss << "undefined socket addr type for " << he->h_addrtype;
        Ss_Core::printLastError(ss.str().c_str());
        std::exit(1);
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
        if (WSAStartup(MAKEWORD(2, 2), &winSockEnv) != OPERATOR_SUCCESS) {
            Ss_Core::printLastError("socket setup failure on windows");
            std::exit(1);
        }
        _socketSetup = true;
    }
}

// on windows socket shutdown
void Ss_Network::winSocketShutdown() {
    // check socket startup in windows and no Network available
    if (_socketSetup && _availableNetworkCount == 0) {
        if (WSACleanup() != OPERATOR_SUCCESS) {
            Ss_Core::printLastError("socket shutdown failure on windows");
            std::exit(1);
        }

        _socketSetup = false;
        std::cout << "socket shutdown success on windows" << std::endl;
    }
}


#endif /* methods for windows platform */
