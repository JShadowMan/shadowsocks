#include "shadowsocks/network/ss_tcp_network.h"


// SsTcpNetwork constructor
SsTcpNetwork::SsTcpNetwork(SsNetwork::NetworkFamily family) :
    SsNetwork(family, NetworkType::NT_TCP) {
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
        return acceptNewConnection();
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

    SsLogger::debug("accept new socket = %d from server = %d", remote, server);
    CLOSE_SOCKET(remote);
}
