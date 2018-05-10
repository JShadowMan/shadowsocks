#ifndef __SHADOWSOCKS_SERVER_INCLUDED__
#define __SHADOWSOCKS_SERVER_INCLUDED__
#pragma once


// other shadowsocks headers
#include "shadowsocks/ss_network.h"


/* `Ss_Server` class */
class Ss_Server {
    public:
        Ss_Server();
        virtual ~Ss_Server();

    public:
        bool startDaemon();
        bool startListening();
        void startServer();
        void stopServer();

    private:
        std::shared_ptr<Ss_Network> _tcp_server;
        std::shared_ptr<Ss_Network> _udp_server;
};


#endif // __SHADOWSOCKS_SERVER_INCLUDED__
