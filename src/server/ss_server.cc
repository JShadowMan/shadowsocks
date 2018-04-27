#include "shadowsocks/ss_network.h"
#include "shadowsocks/server/ss_server.h"


// Ss_Server constructor
Ss_Server::Ss_Server()
    : _tcp_server(Ss_Network::generateTcpMetwork()),
      _udp_server(Ss_Network::generateUdpNetwork()) {
}

// destructor of Ss_Server
Ss_Server::~Ss_Server() {
    delete _tcp_server;
    delete _udp_server;
}

// create daemon and start listening
bool Ss_Server::createDaemon() {
    _tcp_server->listen("0.0.0.0", 9980);
    _udp_server->listen("0.0.0.0", 9980);

    return true;
}
