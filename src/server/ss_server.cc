#include <iostream>
#include "shadowsocks/ss_network.h"
#include "shadowsocks/server/ss_server.h"


#ifdef __linux__
#include <unistd.h>


#endif



// Ss_Server constructor
Ss_Server::Ss_Server()
    : _tcp_server(Ss_Network::generateTcpNetwork()),
      _udp_server(Ss_Network::generateUdpNetwork()) {
}

// destructor of Ss_Server
Ss_Server::~Ss_Server() {
    std::cout << "shadowsocks server instance destructor" << std::endl;
}

// create daemon and start listening
bool Ss_Server::startDaemon() {

#ifdef __linux__
#elif __windows__
    std::cout << "cannot start daemon on windows" << std::endl;
#endif

    return true;
}

// start tcp/udp network listening
bool Ss_Server::startListening() {
    _tcp_server->listen("0.0.0.0", 9980);
    _udp_server->listen("0.0.0.0", 9980);

    return true;
}

// start server(select/poll)
void Ss_Server::startServer() {
    Ss_Network::startSelect();
}

// stop select/poll and exit daemon
void Ss_Server::stopServer() {
    Ss_Network::stopSelect();
}