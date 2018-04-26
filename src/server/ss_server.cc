#include <iostream>
#include "shadowsocks/ss_network.h"
#include "shadowsocks/server/ss_server.h"


// Ss_Server constructor
Ss_Server::Ss_Server()
    : _network(new Ss_Network()) {
}

// destructor of Ss_Server
Ss_Server::~Ss_Server() {
    delete _network;
}

// create daemon and start listening
bool Ss_Server::createDaemon() {
    _network->listen("0.0.0.0", 9980);

    return true;
}
