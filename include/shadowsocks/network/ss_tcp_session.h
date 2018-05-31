#ifndef __SHADOWSOCKS_TCP_SESSION_INCLUDED__
#define __SHADOWSOCKS_TCP_SESSION_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/ss_tcp_network.h"


/**
 * Class: SsTcpSession
 *
 *
 */
class SsTcpSession : public SsTcpNetwork {
    public:
        enum class SessionState : uint8_t {
            SS_INIT = 0x00,
            SS_REQUEST = 0x01,
            SS_ESTABLISHMENT = 0xff
        };

    public:
        explicit SsTcpSession(NetworkFamily family = NetworkFamily::NF_INET_4);
        SsTcpSession(SOCKET fd, sockaddr_storage &ss);
        void readableHandler() final;

    private:
        void onDataReceived();

    private:
        SessionState _stage = SessionState::SS_INIT;
};


#endif // __SHADOWSOCKS_TCP_SESSION_INCLUDED__
