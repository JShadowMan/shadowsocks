#include "shadowsocks/network/ss_tcp_session.h"


// SsTcpSession constructor
SsTcpSession::SsTcpSession(SsNetwork::NetworkFamily family) :
    SsTcpNetwork(family) {
}

// SsTcpSession constructor
SsTcpSession::SsTcpSession(SOCKET fd, sockaddr_storage &ss) :
    SsTcpNetwork(fd, ss) {
}

// override readable handler
void SsTcpSession::readableHandler() {
    if (getState() == NetworkState::NS_LISTEN) {
        auto pair = acceptConnection();

        auto session = std::make_shared<SsTcpSession>(pair.first, pair.second);
        SsSelector::select(session, {SsSelector::SelectorEvent::SE_READABLE});
        return;
    }

    receiveData();
    onDataReceived();
}

// data received event
void SsTcpSession::onDataReceived() {

}

