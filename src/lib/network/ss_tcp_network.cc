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

    SsLogger::debug("socket = %d listening to %s:%d", getSocket(), host, port);
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
        acceptNewConnection();
    } else {
        receiveDate();
    }
}

// writable handler
void SsTcpNetwork::writableHandler() {
}

// from server network accept new client
void SsTcpNetwork::acceptNewConnection() {
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

    auto network = new SsTcpNetwork(remote, ss);
    SsSelector::select(*network, {SsSelector::SelectorEvent::SE_READABLE});
}

// receive data from network
void SsTcpNetwork::receiveDate() {
    static char buffer[1024] = {0};
    int receiveCount = 0;

    receiveCount = ::recv(getSocket(), buffer, BUFFER_BLOCK_SIZE, 0);
    if (receiveCount == 0) {
        throw SsNetworkClosed();
    } else if (receiveCount == OPERATOR_FAILURE) {
        try {
            receiveErrorDetect();
        } catch (SsNetworkClosed &e) {
            __throw_exception_again;
        }
    } else {
        //// test case
        for (auto i = 0; i < receiveCount; ++i) {
            std::printf("0x%02x%c", buffer[i], i == receiveCount - 1 ? '\n' : ' ');
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


    // do nothing on other platform
}
