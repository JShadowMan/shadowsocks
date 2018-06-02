#include "shadowsocks/network/ss_tcp_session.h"


using SsLogger::warning;


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
//    auto flag = _buffers.peekData(0, 0x00);
//    if (_stage == SessionStage::SS_INIT && flag == 0xff) {
//        return;
//    }

    switch (_stage) {
        case SessionStage::SS_INIT: initStageHandle(); break;
        case SessionStage::SS_REQUEST: requestStageHandle(); break;
        case SessionStage::SS_ESTABLISHMENT: establishmentStageHandle();
            break;
    }
}

// when stage equal INIT called
void SsTcpSession::initStageHandle() {
    auto size = _buffers.peekData(1, 0xff);
    if (size != 0xff && _buffers.checkDataSize(2 + size)) {
        auto handshake = _buffers.getDataBlock(2 + size);
        if (handshake[0] != 5) {
            warning("session closed, because handshake not socks5 protocol");
            throw SsNetworkClosed();
        }

        auto it = std::find(std::next(handshake.begin(), 1), handshake.end(), 0);
        if (it == handshake.end()) {
            warning("session closed, because only supported NO AUTHENTICATION");
            ::send(getSocket(), "\x05\xff", 2, 0);
            return;
        }

        std::stringstream ss;
        for (auto i = 2U; i < handshake.size(); ++i) {
            ss << "0x" << std::hex << handshake[i] << std::dec << " ";
        }

        SsLogger::debug("receive handshake, Ver = %d, NMETHOD=%d, METHOD = %s",
            handshake[0], handshake[1], ss.str()
        );

        ::send(getSocket(), "\x05\x00", 2, 0);
        _stage = SessionStage::SS_REQUEST;
    }
}

// when stage equal REQUEST called
void SsTcpSession::requestStageHandle() {
    auto atyp = _buffers.peekData(3, 0xff);
    if (atyp == 1) {
        ipv4RequestHandle();
    } else if (atyp == 4) {
        ipv6RequestHandle();
    } else if (atyp == 3) {
        domainRequestHandle();
    }
}

// when stage equal ESTABLISHMENT called
void SsTcpSession::establishmentStageHandle() {

}

// Ipv4 request
void SsTcpSession::ipv4RequestHandle() {
    // 1(Ver) + 1(CMD) + 1(RSV) + 1(ATYP) + 4(Address) + 2(Port)
    if (_buffers.checkDataSize(10)) {
        auto request = _buffers.getDataBlock(10);
        if (request[0] != 5) {
            warning("session closed, because handshake not socks5 protocol");
            throw SsNetworkClosed();
        }

        SsLogger::debug("ipv4 request");
    }
}

// Ipv6 request
void SsTcpSession::ipv6RequestHandle() {
    // 1(Ver) + 1(CMD) + 1(RSV) + 1(ATYP) + 16(Address) + 2(Port)
    if (_buffers.checkDataSize(22)) {
        auto request = _buffers.getDataBlock(22);
        if (request[0] != 5) {
            warning("session closed, because handshake not socks5 protocol");
            throw SsNetworkClosed();
        }

        SsLogger::debug("ipv6 request");
    }
}

// domain request
void SsTcpSession::domainRequestHandle() {
    // 1(Ver) + 1(CMD) + 1(RSV) + 1(ATYP) + Size(1) _(Address) + 2(Port)
    auto size = _buffers.peekData(4, 0xff);
    if (size != 0xff && _buffers.checkDataSize(7 + size)) {
        auto request = _buffers.getDataBlock(7 + size);
        if (request[0] != 5) {
            warning("session closed, because handshake not socks5 protocol");
            throw SsNetworkClosed();
        }

        SsLogger::debug("domain request");
    }
}
