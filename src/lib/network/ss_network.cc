#include "shadowsocks/network/ss_network.h"


// SsNetwork constructor
SsNetwork::SsNetwork(NetworkFamily family, NetworkType type) :
    _family(family), _type(type), _state(NetworkState::NS_NONE) {
    SsLogger::debug("network created with family = %s, type = %s",
                    family, type);
}

// SsNetwork inter constructor
SsNetwork::SsNetwork(SOCKET fd, sockaddr_storage &ss) :
    _socket(fd), _family(NetworkFamily::NF_INET_4), _type(NetworkType::NT_TCP),
    _state(NetworkState::NS_CONNECT) {
    if (ss.ss_family == static_cast<int>(NetworkFamily::NF_INET_6)) {
        _family = NetworkFamily::NF_INET_6;
    }

    SsLogger::debug("network created with family = %s, type = %s from "
                    "socket = %d", _family, _type, _socket);
}

// SsNetwork destructor
SsNetwork::~SsNetwork() {
    CLOSE_SOCKET(getSocket());
    SsLogger::debug("%s destroy", this);
}

// on a two-tuple listening connection
bool SsNetwork::listen(NetworkHost host, NetworkPort port) {
    if (_state != NetworkState::NS_NONE) {
        SsLogger::error("network cannot from %s state change to %s state",
                        _state, NetworkState::NS_LISTEN);
    }
    _state = NetworkState::NS_LISTEN;
    SsLogger::verbose("%s has changed state to %s", this, _state);

    createSocket();
    if (!doListen(host, port)) {
        SsLogger::emergency("%s listening on %s:%d error", this, host, port);
    }
    SsLogger::info("%s listening on %s:%d", this, host, port);

    return true;
}

// connecting server
bool SsNetwork::connect(NetworkHost host, NetworkPort port) {
    if (_state != NetworkState::NS_NONE) {
        SsLogger::emergency("network cannot from %s state change to %s state",
                            _state, NetworkState::NS_CONNECT);
    }
    _state = NetworkState::NS_CONNECT;
    SsLogger::verbose("%s, change state to %s", this, _state);

    createSocket();
    if (!doConnect(host, port)) {
        SsLogger::emergency("%s listening on %s:%d error", this, host, port);
    }
    SsLogger::debug("%s, connecting to %s:%d", this, host, port);

    return true;
}


// create socket
void SsNetwork::createSocket() {
    _socket = ::socket(static_cast<int>(_family), static_cast<int>(_type), 0);
    if (_socket == INVALID_SOCKET) {
        SsLogger::error("create socket error, errno = %d", errno);
    }
    SsLogger::verbose("created socket = %d", _socket);
}

// create `sockaddr_storage` by host and port
sockaddr_storage SsNetwork::socketAddr(NetworkHost host, NetworkPort port) {
    union {
        sockaddr_storage ss;
        sockaddr_in s4;
        sockaddr_in6 s6;
    } socketAddr{0};

    hostent *he = gethostbyname(host);
    if (he == nullptr) {
        SsLogger::emergency("cannot resolve hostname = %s", host);
    } else {
        if (he->h_addrtype == (short) NetworkFamily::NF_INET_4) {
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

// print network
std::ostream &operator<<(std::ostream &out, SsNetwork *network) {
    out  << "SsNetwork["
        << "family=" << network->_family << ","
        << "type=" << network->_type << ","
        << "socket=" << network->_socket << ","
        << "state=" << network->_state
        << "]";

    return out;
}

// change some opts for socket
bool SsNetwork::setSocketOpts() const {
    int flag = 1;

    SsLogger::verbose("open SO_REUSEADDR flag for  socket = ", _socket);
    return setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&flag,
                      sizeof(flag)) == OPERATOR_SUCCESS;
}

// enable non-blocking
bool SsNetwork::setNonBlocking() const {
#ifdef __linux__
    int flags = fcntl(getSocket(), F_GETFL, 0);
    if (fcntl(getSocket(), F_SETFL, flags | O_NONBLOCK) != OPERATOR_SUCCESS) {
        return false;
    }


#elif __windows__
    u_long openFlag = 1L;
    if (ioctlsocket(_socket, FIONBIO, &openFlag) != OPERATOR_SUCCESS) {
        return false;
    }


#endif

    SsLogger::verbose("toggle non-blocking for socket = %d", _socket);
    return true;
}

// selector callback
void SsNetwork::selectorCallback(SsSelector::SelectorEvent event) {
    try {
        switch (event) {
            case SsSelector::SelectorEvent::SE_READABLE: readableHandler();
                break;
            case SsSelector::SelectorEvent::SE_WRITABLE: writableHandler();
                break;
        }
    } catch (SsNetworkClosed &e) {
        SsSelector::remove(getSocket());
    }
}

// get buffer position
SsBuffer::Buffer &SsNetwork::getBuffer() {
    return _buffers.getBuffer();
}

// update buffer state
void SsNetwork::bufferUpdate(SsBuffer::BufferBlockSize size) {
    _buffers.update(size);
}
