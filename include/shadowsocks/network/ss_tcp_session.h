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
        enum class SessionStage : uint8_t {
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

        void initStageHandle();
        void requestStageHandle();
        void establishmentStageHandle();

        void ipv4RequestHandle();
        void ipv6RequestHandle();
        void domainRequestHandle();

    private:
        SessionStage _stage = SessionStage::SS_INIT;
};


#endif // __SHADOWSOCKS_TCP_SESSION_INCLUDED__
