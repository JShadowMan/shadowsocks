#ifndef __SHADOWSOCKS_TCP_RELAY_INCLUDED__
#define __SHADOWSOCKS_TCP_RELAY_INCLUDED__


#include "shadowsocks/ss_types.h"
#include "shadowsocks/network/ss_tcp_session.h"


/**
 * Class: SsTcpRelay
 *
 *
 */
class SsTcpRelay {
    public:
        SsTcpRelay();
        void startProxy(NetworkHost host, NetworkPort port);

    private:
        std::shared_ptr<SsTcpSession> _proxy;
};


#endif // __SHADOWSOCKS_TCP_RELAY_INCLUDED__
