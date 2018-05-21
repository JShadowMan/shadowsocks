#include "shadowsocks/network/ss_network.h"
#include "shadowsocks/ss_logger.h"


// SsNetwork constructor
SsNetwork::SsNetwork(NetworkFamily family, NetworkType type) :
    _family(family), _type(type), _state(NetworkState::NS_NONE) {
    SsLogger::debug("create network with family = %s, type = %s", family, type);
    createSocket();
}

// on a two-tuple listening
bool SsNetwork::listen(NetworkHost host, NetworkPort port) {
    SsLogger::debug("network = %d, listening on %s:%d", _socket, host, port);
    if (_state != NetworkState::NS_NONE) {
        SsLogger::error("network cannot from %s state change to %s state",
                        _state, NetworkState::NS_LISTEN);
    }
    _state = NetworkState::NS_LISTEN;
    SsLogger::verbose("network = %d, change state to %s", _state);

    return doListen(host, port);
}

// connect an host
bool SsNetwork::connect(NetworkHost host, NetworkPort port) {
    SsLogger::debug("network = %d, connecting to %s:%d", _socket, host, port);
    if (_state != NetworkState::NS_NONE) {
        SsLogger::error("network cannot from %s state change to %s state",
                        _state, NetworkState::NS_CONNECT);
    }
    _state = NetworkState::NS_CONNECT;
    SsLogger::verbose("network = %d, change state to %s", _state);

    return doConnect(host, port);
}

// create socket
void SsNetwork::createSocket() {
    _socket = socket(static_cast<int>(_family), static_cast<int>(_type), 0);
    if (_socket == INVALID_SOCKET) {
        SsLogger::error("create socket error, errno = %d", errno);
    }
    SsLogger::debug("created socket = %d", _socket);
}

// create `sockaddr_storage` by host and port
sockaddr_storage SsNetwork::socketAddr(NetworkHost host, NetworkPort port) {
    union {
        sockaddr_storage ss;
        sockaddr_in s4;
        sockaddr_in6 s6;
    } socketAddr{};

    hostent *he = gethostbyname(host);
    if (he == nullptr) {
        SsLogger::emergency("cannot resolve hostname = %s", host);
    } else {
        if (he->h_addrtype == (int) NetworkFamily::NF_INET_4) {
            socketAddr.s4.sin_family = he->h_addrtype;
            std::memcpy(&socketAddr.s4.sin_addr, he->h_addr_list[0],
                        static_cast<size_t>(he->h_length));
        } else if (he->h_addrtype == (int) NetworkFamily::NF_INET_6) {
            socketAddr.s6.sin6_family = he->h_addrtype;
            std::memcpy(&socketAddr.s6.sin6_addr, he->h_addr_list[0],
                        static_cast<size_t>(he->h_length));
        } else {
            SsLogger::emergency("undefined socket addr type for %d",
                                he->h_addrtype);
        }
    }

    socketAddr.s4.sin_port = htons(static_cast<unsigned short>(port));
    return socketAddr.ss;
}


// print family handle
std::ostream &operator<<(std::ostream &out, SsNetwork::NetworkFamily family) {
    switch (family) {
        case SsNetwork::NetworkFamily::NF_INET_4: out << "IPv4"; break;
        case SsNetwork::NetworkFamily::NF_INET_6: out << "IPv6"; break;
    }

    return out;
}

// print type handle
std::ostream &operator<<(std::ostream &out, SsNetwork::NetworkType type) {
    switch (type) {
        case SsNetwork::NetworkType::NT_TCP: out << "TCP"; break;
        case SsNetwork::NetworkType::NT_UDP: out << "UDP"; break;
        case SsNetwork::NetworkType::NT_RAW: out << "RAW"; break;
    }

    return out;
}

// print network state
std::ostream &operator<<(std::ostream &out, SsNetwork::NetworkState state) {
    switch (state) {
        case SsNetwork::NetworkState::NS_NONE: out << "NONE"; break;
        case SsNetwork::NetworkState::NS_LISTEN: out << "LISTEN"; break;
        case SsNetwork::NetworkState::NS_CONNECT: out << "CONNECT"; break;
    }

    return out;
}
