#include "shadowsocks/network/ss_tcp_network.h"


// SsTcpNetwork constructor
SsTcpNetwork::SsTcpNetwork(SsNetwork::NetworkFamily family) :
    SsNetwork(family, NetworkType::NT_TCP) {
}

// SsTcpNetwork constructor from socket
SsTcpNetwork::SsTcpNetwork(SOCKET fd, sockaddr_storage &ss) :
    SsNetwork(fd, ss) {
}

// do listen for tcp network
bool SsTcpNetwork::doListen(NetworkHost host, NetworkPort port) {
    if (!bind(host, port)) {
        SsLogger::emergency("bind socket = %d to %s:%d error",
                            getSocket(), host, port);
    }

    return ::listen(getSocket(), SOCKET_LISTEN_BACKLOG) != OPERATOR_FAILURE;
}

// do connect for tcp network
bool SsTcpNetwork::doConnect(NetworkHost host, NetworkPort port) {
    SsLogger::debug("connecting to %s:%d", host, port);
    return false;
}

// tcp network bind a socket addr
bool SsTcpNetwork::bind(NetworkHost host, NetworkPort port) const {
    sockaddr_storage addr = socketAddr(host, port);
    auto bindAddr = (sockaddr*) &addr;

    if (!setSocketOpts()) {
        SsLogger::warning("change socket = %d opts error", getSocket());
    }

    if (!setNonBlocking()) {
        SsLogger::warning("enable non-blocking socket %d error", getSocket());
    }

    SsLogger::debug("tcp socket = %d bind to %s:%d", getSocket(), host, port);
    return ::bind(getSocket(), bindAddr, sizeof(addr)) != OPERATOR_FAILURE;
}

// readable handler
void SsTcpNetwork::readableHandler() {
    if (getState() == NetworkState::NS_LISTEN) {
        acceptConnection();
    } else {
        receiveData();
    }
}

// writable handler
void SsTcpNetwork::writableHandler() {
}

// from server network accept new client
void SsTcpNetwork::acceptConnection() {
    sockaddr_storage ss = {0};
#ifdef __linux__
    socklen_t ssLength = sizeof(ss);


#elif __windows__
    int ssLength = sizeof(ss);


#endif

    auto server = getSocket();
    SOCKET remote = ::accept(server, (struct sockaddr*) &ss, &ssLength);
    if (remote == INVALID_SOCKET) {
        SsLogger::error("invalid client socket from server = %d", server);
    }

    NetworkHost host;
    NetworkPort port;
    if (ss.ss_family == static_cast<int>(SsNetwork::NetworkFamily::NF_INET_4)) {
        host = inet_ntoa(((struct sockaddr_in*) &ss)->sin_addr);
        port = ntohs(((struct sockaddr_in*) &ss)->sin_port);

        SsLogger::debug("accept new socket = %d, addr = %s:%d from server = %d",
                        remote, host, port, server);
    } else {
        /**
         * @todo windows inet_ntop
         */
        SsLogger::warning("current unsupported Ipv6 address convert");
    }

    auto network = std::make_shared<SsTcpNetwork>(remote, ss);
    SsSelector::select(network, {SsSelector::SelectorEvent::SE_READABLE});
}

// receive data from network
void SsTcpNetwork::receiveData() {
    int receiveByteCount = 0;
    while (true) {
        auto &buffer = getBuffer();

        receiveByteCount = ::recv(getSocket(), buffer.first, buffer.second, 0);
        if (receiveByteCount == 0) {
            throw SsNetworkClosed();
        } else if (receiveByteCount == OPERATOR_FAILURE) {
            receiveErrorDetect();
        }

        auto temp = buffer.second;
        bufferUpdate(receiveByteCount);

        if (receiveByteCount != temp) {
            break;
        }
    }
}

// detect error in receive data
void SsTcpNetwork::receiveErrorDetect() {
#ifdef __windows__
    switch (WSAGetLastError()) {
        case CONNECTION_RESET_BY_PEER:
            throw SsNetworkClosed();
        default: {
            SsLogger::emergency("receive data error");
        }
    }


#endif


    if (errno != OPERATOR_SUCCESS) {
        SsLogger::emergency("receive data error occurs, message = %s",
                            strerror(errno));
    }
}
